#include <ansi.h>
#define SKILL_NAME "iron wall"
#define SKILL_NAME_C "鐵壁"
#define SKILL_CLASS "activity"

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

string *defend_message = ({
    HIW"「噹」地一聲，$N"HIW"用身體的鐵甲擋住了$n的攻擊。\n"NOR,
    HIW"$n"HIW"用力朝$N"HIW"攻擊卻被$N的鐵甲所擋住。\n"NOR,
    HIW"$N"HIW"將鐵盾舉到胸前，硬是擋下了$n的攻擊。\n"NOR,
});

// target 受到傷害前，讓技能先跑過 receive_damage 
// 如何便可以製作 "暫時無敵技" 或是 "傷害吸收盾" 之類的技能
int receiveDamage(object me, object target, int damage)
{
    int ratio, sk;
    string msg;

    sk = me->query_skill(SKILL_NAME);

    if( me->query_skill(SKILL_NAME) < 20 ) return damage;
    ratio = sk/10;

    // 訊息
    // 練滿有 20% 的機會吸收傷害 600
    if( ratio > random(100) ) {
        msg = defend_message[random(sizeof(defend_message))];
        message_vision(msg, me, target);
        if( damage <= sk*3 ) {
            message_vision(HIW"$N"HIW"完全防禦了$n"HIW"的攻擊，沒有造成任何傷害。\n"NOR, me, target);
            me->damage_stat("mp", random(damage/10) + 1, me);
            return 0;
        } else {
            damage = damage - sk*3;
            message_vision(HIW"$N"HIW"雖然使用鐵壁抵擋攻擊，仍然被破防禦造成"HIR"("+damage+")"HIW"點傷害。\n"NOR, me, target);
            me->damage_stat("mp", random(sk*3/10), me);
        }
        // 增加技能經驗
        me->improve_skill(SKILL_NAME, 1);
        return damage;
    }
    return damage;
}
