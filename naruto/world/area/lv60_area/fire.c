#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "火山內部");
    set("x_axis_size", 21);            // 橫向大小
    set("y_axis_size", 21);            // 縱向大小
    setup();
}
void init()
{
    add_action("do_recall", "recall");
    add_action("do_recall", "quit");
    add_action("do_recall", "move");
    add_action("do_recall", "sfly");
    add_action("do_not", "assign");
    add_action("do_not", "remember");
}
int do_recall(string arg)
{
    if( this_player()->query_condition("calcification")) {
        tell_object(this_player(), "你現在的狀況不允許你這樣做。\n");
        return 1;
    }
}
int do_not(string arg)
{
    tell_object(this_player(), "這裡的磁波影響過大，無法記憶任何東西。\n");
    return 1;
}
int valid_leave(object me, string dir)
{
    object ob;
    int x, y, damage;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    ob = this_object();

    // return 0; 表示移動失敗
    if( me->query_condition("calcification") ) {
        if( random(me->query_ability("exact")) > random(200) ) {
            message_vision(HIW"$N立刻從石灰中掙脫出來了！\n"NOR, me);
            me->start_busy(1);
            me->delete_condition("calcification");
        } else {
            message_vision(HIW"$N被石灰給困住了，動彈不得！\n"NOR, me);
            me->start_busy(3);
        }
        return 1;
    }
    if( userp(me) && ob->query_data(x, y, "fire") ) {
        damage = 20 + random(150);
        me->receive_damage(damage, this_object());
        message_vision(HIR"$N不小心被滾燙的炎漿燙傷了！"NOR"("HIY+damage+NOR")\n", me);
    }
    return ::valid_leave(me, dir);
}
