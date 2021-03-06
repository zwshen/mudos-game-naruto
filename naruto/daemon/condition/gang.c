#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("gang");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    mapping mcnd;
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIW"$N似乎無法保持防禦狀態了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}