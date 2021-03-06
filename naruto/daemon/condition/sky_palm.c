// 八卦回天

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("sky_palm");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !me->is_fighting() ) {
        message_vision(HIW"\n$N將查克拉回收，停止繼續使用"HIG"八卦回天"HIW"。\n\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIW"\n$N因為注意力不佳，只好暫時停用"HIG"八卦回天"HIW"。\n\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}
