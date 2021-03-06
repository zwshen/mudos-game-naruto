inherit AREA;

void create()
{
    set("name", "小荒島");
    set("x_axis_size", 49);            // 橫向大小
    set("y_axis_size", 49);            // 縱向大小
    setup();
    set("no_recall", 1);
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 15 && y == 11 && dir == "north" ) return 0;
    return ::valid_leave(me, dir);
}
void init()
{
    add_action("do_jump", "jump");
}
int do_jump(string arg)
{
    object me, area;
    string area_file = "/world/area/benthal/sea8.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "海" && arg != "海岸" && arg != "汪洋大海") return 0;
    if( me->query("area_info/x_axis") != 24 || me->query("area_info/y_axis") != 3 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N深深吸了一口氣，捏著鼻子往大海一跳！\n", me);
    if( !area_move(area, me, 38, 48) ) return 0;
    message_vision("$N從海面沉了下來，身旁都是氣泡。\n", me);

    return 1;
}
