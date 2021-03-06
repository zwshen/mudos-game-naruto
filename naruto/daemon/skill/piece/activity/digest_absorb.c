#include <ansi.h>
#define SKILL_NAME "digest absorb"
#define SKILL_NAME_C "消化吸收"
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

int wittiness(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

int evade(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/20;
}

// 檢查是否能使用技能
int isCast(object me, string act, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "check" ) {
        tell_object(me, "目前"+SKILL_NAME_C+"有 check 這個功\能。\n");
        return 0;
    }

    if( me->query_condition("da_busy") ) {
        tell_object(me, "你才剛使用過消化吸收，稍微休息一下再用吧。\n");
        return 0;
    }

    if( sk < 60 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk*3/2 ) {
        tell_object(me, "你的狀態無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("da", 1) != 0) {
        tell_object(me, "你已經在使用" + SKILL_NAME_C + "技巧了。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{
    mapping cnd = ([]);

    me->damage_stat("mp", sk*3/2, me);
    message_vision("$N閉目使用"HIW"「生命歸返•消化吸收」"NOR"，身體忽胖忽瘦...\n"NOR, me);

    cnd["name"] = HIW+SKILL_NAME_C+NOR;
    cnd["duration"] = sk/8;
    cnd["hp"] = me->query_stat_maximum("hp")*(sk/100)/100;

    me->set_condition("da", cnd);

    cnd["name"] = HIW+"(CD)消化"+NOR;
    cnd["duration"] = sk/2;

    me->set_condition("da_busy", cnd);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}
