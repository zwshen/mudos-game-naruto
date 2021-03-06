// 給考場 npc 用的 by mouse 2007/7/26

#include <ansi.h>
#define SKILL_NAME "noshadow step"
#define SKILL_NAME_C "無影腳"
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
    HIW"$N"HIW"腳下步伐連踏，瞬間消失在$n的眼前。\n"NOR,
    HIW"$N"HIW"使出「無影腳」在$n還沒注意到時就繞到後方了。\n"NOR,
    HIW"$N"HIW"忽然出現在$n的身後，把$n嚇了一大跳。\n"NOR,
});

// target 受到傷害前，讓技能先跑過 receive_damage 
// 如何便可以製作 "暫時無敵技" 或是 "傷害吸收盾" 之類的技能
int receiveDamage(object me, object target, int damage)
{
    int ratio;
    string msg;
    if( me->query_skill(SKILL_NAME) < 20 ) return damage;
    ratio = me->query_skill(SKILL_NAME)*10/200;
    
    // 練滿有 10% 的機會完全吸收傷害
    if( ratio < random(100) ) return damage;

    // 訊息
    msg = defend_message[random(sizeof(defend_message))];
    message_vision(msg, me, target);

    // 損失mp
    me->damage_stat("mp", random(damage/10) + 1, me);
    
    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);
    
    return 0;
}
