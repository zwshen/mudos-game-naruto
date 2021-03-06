// 強化系念技：肉體強化(body strength) 
// create by tmr 2005/10/20
// update bye acme 2007.03.16
// 增加附加能力 by mouse 2007/7/25

#include <ansi.h>
#define SKILL_NAME   "body strength"
#define SKILL_NAME_C "肉體強化"
#define SKILL_CLASS  "strength"

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
    return ability + me->query_skill(SKILL_NAME)/10;
}

int attack(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

void do_perform(object me)
{
    int sk_lv;

    mapping cnd = ([]);

    sk_lv =  me->query_skill(SKILL_NAME);

    if( me->query_skill( SKILL_NAME, 1) < 30 || me->query_skill("strength", 1) < 30  ) {
        write("你的能力不足以使用這個技能。\n");
        return;
    }
    if( me->query_stat("mp") < sk_lv*3/2 ) {
        write("你目前沒有足夠的念力來使用肉體強化。\n");
        return;
    }
    if( me->query_condition("body_strength_cond") != 0 ) {
        write("你正在施展肉體強化了。\n");
        return;
    }
    me->damage_stat("mp", sk_lv*3/2, me);

    message_vision("$N全身肌肉爆漲，施展出"HIY"肉體強化"NOR"！！\n", me);

    cnd["name"] = HIY"肉體強化"NOR;
    cnd["duration"] = sk_lv*2;
    cnd["attack"] = sk_lv/3;
    cnd["armor"] = sk_lv/3;

    me->set_condition("body_strength_cond", cnd);

    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);
    me->improve_skill("strength", 1);
    me->start_busy(1);
}

int perform_action(object me, string act, object target)
{
    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用肉體強化。\n");

    switch( act ) {
        case "powerup": do_perform(me); break;
        default: return notify_fail("目前肉體強化術有 powerup 這個功\能。\n"); break;
    }
    return 1;
}
