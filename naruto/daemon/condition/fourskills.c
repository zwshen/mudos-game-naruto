// 風林火山

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("fourskills");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision("$N"CYN"身上風林火山的效果已經快速消失了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    mapping mcnd;
    
    if( !mapp(mcnd = me->query_condition(cnd)) ) mcnd = ([]);
    
    mcnd["duration"] = cnd_data["duration"];
    
    me->add_temp("apply/exact", 100 );          // 增加命中能力
    me->add_temp("apply/evade", 100 );          // 增加迴避能力
    me->add_temp("apply/attack", 100 );         // 增加攻擊力量
    me->add_temp("apply/armor", 100 );          // 增加防禦力量
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "fourskills" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("fourskills");
    if( !cnd_data ) return;

    me->add_temp("apply/exact", -100 );          // 減少命中能力
    me->add_temp("apply/evade", -100 );          // 減少迴避能力
    me->add_temp("apply/attack", -100 );         // 減少攻擊力量
    me->add_temp("apply/armor", -100 );          // 減少防禦力量
}
