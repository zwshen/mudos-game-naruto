// holy_hand_cond 聖療之手
// tmr 2005/10/22

#include <ansi.h>
inherit CONDITION;
#define COND_NAME "holy_hand_cond"

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon( COND_NAME );
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        me->delete_condition(cnd);
        return;
    }
}
