#include <ansi.h>
#define SKILL_NAME "gun ten"
#define SKILL_NAME_C "十指槍"
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

int intimidate(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*2;
    j = COMBAT_D->wittiness(target, 1) + COMBAT_D->evade(target, me, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk*4 + me->query_skill("martial") + me->query_skill("gun finger");

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

int autoCasting(object me, object target, object weapon)
{
    string *name = ({ "肩膀", "右大腿", "肚子", "右臂", "背部", "右小腿", "胸口", 
                      "左大腿", "左臂", "左小腿", "右腕", "左腕", "軀幹", "身軀",
                      "膝蓋\", "膝部", });

    int damage, sk;
    mapping cnd = ([]);

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/3 ) return 1;
    if( me->query_skill("martial", 1) < 160 ) return 1;
    if( me->query_skill("gun finger", 1) < 100 ) return 1;
    if( sk < 60 ) return 1;

    if( sk < 80 ) {                          // 20~80 級 5%
        if( random(sk) < sk*19/20 ) return 1;
    } else if( sk < 150 ) {                  // 81~150 級 10%
        if( random(sk) < sk*9/10 ) return 1;
    } else {                                 // 151~200 級 20%
        if( random(sk) < sk*8/10 ) return 1;
    }
    message_vision("$N將十根手指上下咬合，對準$n使出"HIR"『"RED"十指槍"HIR"』"NOR"十根手指一同刺向$n！\n", me, target);
    if( !isHit(me, target) ) {
        message_vision("$n一個迴旋踢踢中$N的手指，正好將$N的攻擊路境打亂了。\n", me, target);
    } else {
        damage = getDamage(me, target, sk);
        target->receive_damage(damage, me);
        message_vision( sprintf("「噗」地數聲，$N的手指插進$n"+name[random(sizeof(name))]+"留下了十個深深的窟窿(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
        if( sk >= 120 ) {

            cnd["name"] = RED+"失血狀態"+NOR;
            cnd["duration"] = sk/20;
            cnd["from"] = me;

            target->set_condition("blood", cnd);
        }
    }
    me->damage_stat("mp", sk/3, me);
    me->improve_skill(SKILL_NAME, 1);
    return 1;
}