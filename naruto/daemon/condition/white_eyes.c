// 白眼

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("white_eyes");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 || me->query_stat("mp") < 5 ) {
        message_vision(HIW"$N眼睛旁的青筋慢慢退去了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    me->damage_stat("mp", 5, me);
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    mapping mcnd;
    
    if( !mapp(mcnd = me->query_condition(cnd)) ) mcnd = ([]);
    
    mcnd["duration"] = cnd_data["duration"];

    me->add_temp("apply/evade", mcnd["evade"] );           // 增加迴避能力
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "white_eyes" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("white_eyes");
    if( !cnd_data ) return;

    me->add_temp("apply/evade", -cnd_data["evade"] );
}
