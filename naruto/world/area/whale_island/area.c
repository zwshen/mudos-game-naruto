inherit AREA;

void create()
{
    set("name", "鯨魚島");
    set("x_axis_size", 49);            // 橫向大小
    set("y_axis_size", 49);            // 縱向大小
    setup();
}
void init()
{
    add_action("do_jump", "jump");
}
int do_jump(string arg)
{
    string area_file = "/world/area/benthal/sea9.c";
    object me, area;
    int x, y;

    me = this_player();
    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( !arg ) return 0;
    if( arg != "海" && arg != "海面" && arg != "碼頭" ) return 0;

    if( x == 22 && y == 45 || x == 22 && y == 46 || x == 22 && y == 47 ) {
        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        message_vision("$N看了看海面，深吸一口氣跳了下去。\n", me);
        if( !area_move(area, me, 21, 1) ) return 0;
        message_vision("$N從海面上沉了下來。\n", me);
        return 1;
    }
    return 0;
}
