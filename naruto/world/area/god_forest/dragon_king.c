#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "龍王ソ巢");
    set("x_axis_size", 21);            // 橫向大小
    set("y_axis_size", 11);            // 縱向大小
    setup();
    set("no_recall", 1);
}
int valid_leave(object me, string dir)
{
    object ob;
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    ob = this_object();

    // return 0; 表示移動失敗
    if( userp(me) && x == 10 && y == 2 && dir == "north"
        || userp(me) && x == 9 && y == 1 && dir == "east"
        || userp(me) && x == 11 && y == 1 && dir == "west") {

        if( me->query_level() <= 40 ) me->move(__DIR__"king1.c");
        else me->move(__DIR__"king2.c");
        return 1;
    }
    if( !userp(me) && x == 10 && y == 2 && dir == "north"
        || !userp(me) && x == 9 && y == 1 && dir == "east"
        || !userp(me) && x == 11 && y == 1 && dir == "west") return 0;

    return ::valid_leave(me, dir);
}
