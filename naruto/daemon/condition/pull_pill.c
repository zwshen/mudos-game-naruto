// 拔農作物用的

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("pull_pill");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(CYN"$N甩頭想了想，現在回去應該不會被抓了吧。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
}
