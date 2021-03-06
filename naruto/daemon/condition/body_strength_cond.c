#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("body_strength_cond");
}

// 每 update 一次 消秏時效一點..
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        me->delete_condition(cnd);
        return;
    }
}

void condition_apply(object me, string cnd, mapping cnd_data)
{
    me->add_temp("apply/attack", cnd_data["attack"] );          // 增加攻擊力
    me->add_temp("apply/armor", cnd_data["armor"] );            // 增加防禦力
}

void condition_unapply(object me, string cnd, mapping cnd_data)
{
    me->add_temp("apply/attack", -cnd_data["attack"] );
    me->add_temp("apply/armor", -cnd_data["armor"] );
}
