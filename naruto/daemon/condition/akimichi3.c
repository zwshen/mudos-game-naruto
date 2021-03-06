// 秋道秘藥 菠菜丸、咖哩丸使用

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("akimichi3");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( me->query_temp("chili_blood") >= 10 ) {
        message_vision(HIR"$N忽然吐出一大口鮮血，簡直就快倒在地上了。\n"NOR, me);
        me->receive_damage(me->query_stat("hp")*4/5, me);
        me->damage_stat("ap", me->query_stat("ap")*4/5, me);
        me->set_temp("chili_blood", 0);
    }
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(CYN"$N看起來似乎好多了。\n"NOR, me);
        me->delete_condition(cnd);
        me->delete_temp("chili_blood");
        return;
    }
    me->add_temp("chili_blood", 1);
}
void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "akimichi3" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("akimichi3");
    if( !cnd_data ) return;

    // 以防萬一，在這裡也刪一次吐血temp
    me->delete_temp("chili_blood");
}
