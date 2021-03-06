// 魂體轉換用冷卻倉

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("ghost_change_down");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIW"$N似乎感覺精神好多了\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    mapping mcnd;
    
    if( !mapp(mcnd = me->query_condition(cnd)) ) mcnd = ([]);
    
    mcnd["duration"] = cnd_data["duration"];
    
    me->add_temp("apply/str", -mcnd["str"] );   // 減少
    me->add_temp("apply/dex", -mcnd["dex"] );   // 減少
    me->add_temp("apply/con", -mcnd["con"] );   // 減少
    me->add_temp("apply/int", -mcnd["int"] );   // 減少
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "ghost_change_down" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("ghost_change_down");
    if( !cnd_data ) return;

    me->add_temp("apply/str", cnd_data["str"] );   // 增加
    me->add_temp("apply/dex", cnd_data["dex"] );   // 增加
    me->add_temp("apply/con", cnd_data["con"] );   // 增加
    me->add_temp("apply/int", cnd_data["int"] );   // 增加
}
