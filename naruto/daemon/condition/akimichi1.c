// 秋道秘藥 菠菜丸、咖哩丸使用

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("akimichi1");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(CYN"$N看起來似乎好多了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    mapping mcnd;
    
    if( !mapp(mcnd = me->query_condition(cnd)) ) mcnd = ([]);
    
    mcnd["duration"] = cnd_data["duration"];

    me->add_temp("apply/ap", mcnd["ap"] );     // 精力
    me->add_temp("apply/hp", mcnd["hp"] );     // 體力
    me->add_temp("apply/mp", mcnd["mp"] );     // 魔力

    if( me->query_stat("ap") > me->query_stat_maximum("ap") ) me->set_stat_current("ap", me->query_stat_maximum("ap"));
    if( me->query_stat("hp") > me->query_stat_maximum("hp") ) me->set_stat_current("hp", me->query_stat_maximum("hp"));
    if( me->query_stat("mp") > me->query_stat_maximum("mp") ) me->set_stat_current("mp", me->query_stat_maximum("mp"));
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "akimichi1" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("akimichi1");
    if( !cnd_data ) return;

    me->add_temp("apply/ap", -cnd_data["ap"] );
    me->add_temp("apply/hp", -cnd_data["hp"] );
    me->add_temp("apply/mp", -cnd_data["mp"] );

    if( me->query_stat("ap") > me->query_stat_maximum("ap") ) me->set_stat_current("ap", me->query_stat_maximum("ap"));
    if( me->query_stat("hp") > me->query_stat_maximum("hp") ) me->set_stat_current("hp", me->query_stat_maximum("hp"));
    if( me->query_stat("mp") > me->query_stat_maximum("mp") ) me->set_stat_current("mp", me->query_stat_maximum("mp"));
}
