#include <ansi.h>
#define SKILL_NAME "animal yan"
#define SKILL_NAME_C "獸嚴"
#define SKILL_CLASS "martial"

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

string query_class() { return SKILL_CLASS; }

void skill_advanced(object me, string skill)
{
    int lv = me->query_skill(skill, 1);
    switch( lv ) {
        case 189: me->set_skill_require(skill, 1500000); break; // 關卡3 : 189升190
        case 149: me->set_skill_require(skill, 1000000); break; // 關卡2 : 149升150
        case  99: me->set_skill_require(skill, 500000);  break; // 關卡1 :  99升100
        default:  me->set_skill_require(skill, lv*lv*5); break;
    }
}

int wittiness(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*2;
    j = COMBAT_D->wittiness(target, 1) + COMBAT_D->intimidate(target, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage;
    object wp;

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    if( sk < 100 ) return damage;              // 100%
    else if( sk < 120 ) return damage*11/10;   // 110%
    else if( sk < 150 ) return damage*6/5;     // 120%
    else if( sk < 180 ) return damage*13/10;   // 130%
    else if( sk < 199 ) return damage*3/2;     // 150%
    else return damage*7/4;                    // 175%
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    if( !hit ) {
        me->damage_stat("mp", sk/12, me);
    } else {
        me->damage_stat("mp", sk/6, me);
    }
    me->improve_skill(SKILL_NAME, 1);
}

int autoCasting(object me, object target, object weapon)
{
    string *name = ({ "肩膀", "右大腿", "肚子", "右臂", "背部", "右小腿", "胸口", 
                      "左大腿", "左臂", "左小腿", "右腕", "左腕", "軀幹", "身軀",
                      "膝蓋\", "膝部", "要害", "屁股", "鼻子", });

    string msg = name[random(sizeof(name))];
    int damage, sk, hit;

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/6 ) return 1;
    if( me->query_skill("martial", 1) < 80 ) return 1;
    if( sk < 40 ) return 1;

    if( sk < 80 ) {
        if( random(sk) < sk*9/10 ) return 1; // 20~80 級 10%
    } else if( sk < 150 ) {
        if( random(sk) < sk*8/10 ) return 1; // 81~150 級 20%
    } else {
        if( random(sk) < sk*7/10 ) return 1; // 151~200 級 30%
    }
    message_vision("$N右手握拳，以指槍的速度揮出快速拳"HIR"『"HIY"獸嚴"HIR"』"NOR"一拳打向$n的"+msg+"！\n", me, target);

    hit = COMBAT_D->isHit(me, target);

    if( !hit ) {
        message_vision("「啪」地一聲，$N軟弱無力的拳頭打在$n"+msg+"，$n一點事也沒有。\n", me, target);
        me->damage_stat("mp", sk/12, me);
    } else {
        damage = getDamage(me, target, sk);
        target->receive_damage(damage, me);
        message_vision( sprintf("「碰」地一聲$n整個人飛了出去，受創的"+msg+"部位更是痛苦難耐(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
        if( random(sk) > sk*7/10 ) {
            damage = damage/2 + random(30);
            message_vision("$N趁勝追擊，順勢向前使出「"HIW"指槍"NOR"」戳向$n的"+msg+"部位。\n", me, target);
            target->receive_damage(damage, me);
            message_vision( sprintf("「噗」地一聲$n"+msg+"再次受到二次創傷(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
            me->improve_skill(SKILL_NAME, 1);
        }
    }
    setEffect(me, sk, hit);
    return 1;
}