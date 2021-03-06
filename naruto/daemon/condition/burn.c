/* burn.c 
   扣生命值的燙傷狀態，傷害依照sk攻擊力而改變

   資料結構
   ([ "duration": 時效 ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("burn");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(YEL"$N"YEL"所受的燙傷似乎沒那麼嚴重了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    // 扣除生命值, 敘述
    message_vision( sprintf("$N"YEL"被燙的不停在地上打滾...(%d) %s\n", cnd_data["damage"], COMBAT_D->report_status(me) ), me);
    if( objectp(cnd_data["from"]) ) me->damage_stat("hp", cnd_data["damage"], cnd_data["from"]);
    else me->damage_stat("hp", cnd_data["damage"], me);
}