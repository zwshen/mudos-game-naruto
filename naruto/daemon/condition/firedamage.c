/* firedamage.c 
   扣生命值的著火狀態

   資料結構
   ([ "duration": 時效 ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("firedamage");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIR"火燄似乎已經熄滅了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    // 扣除生命值, 敘述
    message_vision( sprintf("$N"HIR"被身上的火燄燒地哇哇大叫...(%d) %s\n", 50, COMBAT_D->report_status(me) ), me);
    if( objectp(cnd_data["from"]) ) me->damage_stat("hp", 50, cnd_data["from"]);
    else me->damage_stat("hp", 50, me);
}