/* 蠍毒 
   依照生命最大值1%扣除的中毒狀態

   資料結構
   ([ "duration": 時效 ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("scorpion_poison");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    int i = me->query_stat_maximum("hp")/100;
    if( i > 200 ) i = 200;

    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        message_vision(HIM"$N身上的中毒似乎已經減輕了。\n"NOR, me);
        me->delete_condition(cnd);
        return;
    }
    // 扣除生命值, 敘述
    message_vision( sprintf("$N"MAG"臉色一陣痛苦，傷口流出黑色血液...(%d) %s\n", i, COMBAT_D->report_status(me) ), me);
    if( objectp(cnd_data["from"]) ) me->damage_stat("hp", i, cnd_data["from"]);
    else me->damage_stat("hp", i, me);
}