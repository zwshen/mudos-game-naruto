// 鑄造

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("founder");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( me->query_temp("founder") >= 10 ) {
        message_vision(HIC"$N用力的踩著風爐，不停給鍋爐加溫。\n"NOR, me);
        me->add_temp("founder2", 1);
        me->set_temp("founder", 0);
    }
    if( me->query_temp("founder2") >= 10 ) {
        message_vision(HIR"$N注意著材料的燒結程度，就怕一時晃神出了差錯。\n"NOR, me);
        me->set_temp("founder2", 0);
    }
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIY"鍋爐的溫度快速下降，液態合金已經完成，該進行最後工作(getwp)了。\n"NOR, me);
        me->delete_condition(cnd);
        me->delete_temp("founder");
        me->delete_temp("founder2");
        me->start_busy(1);
        return;
    }
    me->start_busy(2);
    me->add_temp("founder", 1);
}
void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "founder" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("founder");
    if( !cnd_data ) return;

    // 以防萬一，在這裡也刪一次temp
    me->delete_temp("founder");
    me->delete_temp("founder2");
}
