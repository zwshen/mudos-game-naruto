#include <ansi.h>
#define SKILL_NAME "gun gentian"
#define SKILL_NAME_C "指槍•黃蓮"
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

int attack(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/4;
}

// 計算人數
int check_number(object me, int sk)
{
    int number;

    if( sk < 120 ) {
        number = 1;
    } else {
        number = sk/50;
    }
    return number;
}

// 計算是否命中
int isHit(object me, object target)
{
    int hit, raiseHit;

    raiseHit = me->query_ability("exact")/4;

    me->add_temp("apply/exact", raiseHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -raiseHit);

    return hit;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk*3 + me->query_skill("martial") + me->query_skill("gun finger")*2;

    if( wp = me->query_temp("weapon/twohanded") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else if( wp = me->query_temp("weapon/righthand") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else if( wp = me->query_temp("weapon/lefthand") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else raiseDamage -= COMBAT_D->isDamage(me, target, 0)*3/4;

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
                      "膝蓋\", "膝部", "護額", "衣衫", "內褲", "錢袋", "鼻孔",
                      "肚臍", "褲子", "護目鏡", "眼鏡", });

    int damage, sk, i, number;

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( me->query_stat("mp") < 200 ) return 1;
    if( me->query_skill("martial", 1) < 200 ) return 1;
    if( me->query_skill("gun finger", 1) < 80 ) return 1;
    if( sk < 60 ) return 1;

    if( sk < 80 ) {
        if( random(sk) < sk*9/10 ) return 1; // 20~80 級 10%
    } else if( sk < 150 ) {
        if( random(sk) < sk*8/10 ) return 1; // 81~150 級 20%
    } else {
        if( random(sk) < sk*7/10 ) return 1; // 151~200 級 30%
    }
    number = check_number(me, sk);

    message_vision("$N使出指槍戳向$n，在碰到$n身子的時候忽然攻勢一收變招為"HIY"『"HIR"指槍•黃蓮"NOR+HIY"』"NOR"！\n", me, target);

    for(i=0;i<number;i++) {
        if( i > 3 ) break;        // 最多打四下
        if( !isHit(me, target) ) {
            message_vision("$n似乎能夠看清$N攻擊的路線，完全沒被打到。\n", me, target);
        } else {
            damage = getDamage(me, target, sk);
            target->receive_damage(damage, me);
            message_vision( sprintf("$n的"+name[random(sizeof(name))]+"、"+name[random(sizeof(name))]+"、"+name[random(sizeof(name))]+"等部位被$N刺擊受到了嚴重傷害(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
        }
    }
    me->damage_stat("mp", 50*i, me);
    me->improve_skill(SKILL_NAME, 1);
    return 1;
}