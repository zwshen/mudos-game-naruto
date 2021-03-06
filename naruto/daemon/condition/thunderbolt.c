#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("thunderbolt");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !me->is_fighting() ) {
        message_vision(HIK"因為停止戰鬥$N將黑雲分解了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIK"因為等待時間太長所以黑雲消散了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}