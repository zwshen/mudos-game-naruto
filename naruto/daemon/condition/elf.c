// 幻想妖精

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("elf");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIW"$N的身影慢慢地顯現出來。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    mapping mcnd;
    
    if( !mapp(mcnd = me->query_condition(cnd)) ) mcnd = ([]);
    
    mcnd["duration"] = cnd_data["duration"];
    
    me->add_temp("apply/evade", mcnd["evade"] );  // 增加迴避能力
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "elf" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("elf");
    if( !cnd_data ) return;

    me->add_temp("apply/evade", -cnd_data["evade"] );
}
