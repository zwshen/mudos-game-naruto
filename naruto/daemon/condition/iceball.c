#include <ansi.h>

inherit CONDITION;

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$N" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$N" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$N" + HIR + ratio + "%" + HIK"]\n"NOR;
}

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("iceball");
}
void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {

        // 玩家對玩家沒有冰爆
        if( userp(cnd_data["from"]) && userp(me) ) {
            me->delete_condition(cnd);
            return;
        }
        // 找不到使用者就隨便受點傷
        if( !objectp(cnd_data["from"]) ) me->receive_damage(50, me);
        else me->receive_damage(cnd_data["damage"], cnd_data["from"]);

        message_vision(HIC"冰塊受不了四周的影響，忽然急速爆裂讓"NOR"$N"HIC"受到重創！("HIR+cnd_data["damage"]+HIW")"+report_status(this_object())+""NOR, me);
        me->delete_condition(cnd);
        return;
    }
    // 敘述
    message_vision("$N"HIW"被冰凍的身子發出陣陣寒氣...\n"NOR, me);
}
