#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "郊外沙區");
    set("x_axis_size", 31);            // 橫向大小
    set("y_axis_size", 31);            // 縱向大小
    setup();
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 21 && y == 1 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 22 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 23 && y == 1 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
void init()
{
    add_action("do_dig", "dig");
    if( userp(this_player()) && this_player()->hasCamp("sand_bandit") == 0 ) {
        tell_object(this_player(),HIR"這裡的沙穴強盜們似乎不太歡迎你。\n"NOR);
        this_player()->setCamp("sand_bandit", -34999);
    }
}
int do_dig(string arg)
{
    object me, area;
    string area_file = "/world/area/sand_hole/hole_1b.c";

    me = this_player();

    if( me->is_busy() ) return notify_fail("你現在正在忙，一時之間無法移動。\n");

    if( me->query("area_info/x_axis") == 4 && me->query("area_info/y_axis") == 4 ||
        me->query("area_info/x_axis") == 14 && me->query("area_info/y_axis") == 3 ||
        me->query("area_info/x_axis") == 25 && me->query("area_info/y_axis") == 10 ||
        me->query("area_info/x_axis") == 14 && me->query("area_info/y_axis") == 13 ||
        me->query("area_info/x_axis") == 0 && me->query("area_info/y_axis") == 13 ||
        me->query("area_info/x_axis") == 5 && me->query("area_info/y_axis") == 18 ||
        me->query("area_info/x_axis") == 16 && me->query("area_info/y_axis") == 21 ||
        me->query("area_info/x_axis") == 27 && me->query("area_info/y_axis") == 26 ) {

        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        message_vision("$N像隻土撥鼠般瘋狂的挖掘地面...挖出一個大坑跌了進去...\n", me);
        if( !area_move(area, me, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) return 0;
        message_vision("$N從上面跌了下來，滿臉的沙土。\n", me);
        return 1;
    }
    return notify_fail("這裡的沙子似乎沒什麼好挖的。\n");
}
