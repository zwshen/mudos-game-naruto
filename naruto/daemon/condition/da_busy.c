// 消化吸收冷卻時間

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("da_busy");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        tell_object(me, HIW"你的身體似乎又可以自由控制了。\n"NOR);
        me->delete_condition(cnd);
        return;
    }
}
