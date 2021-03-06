inherit AREA;

void create()
{
    set("name", "地下沙穴B-1");
    set("x_axis_size", 31);            // 橫向大小
    set("y_axis_size", 31);            // 縱向大小
    setup();
}
int valid_leave(object me, string dir)
{
    object ob;
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    ob = this_object();

    if( userp(me) && ob->query_data(x, y, "northeast") && dir == "northeast"
        || userp(me) && ob->query_data(x, y, "northwest") && dir == "northwest"
        || userp(me) && ob->query_data(x, y, "southeast") && dir == "southeast"
        || userp(me) && ob->query_data(x, y, "southwest") && dir == "southwest"
        || userp(me) && ob->query_data(x, y, "north") && dir == "north"
        || userp(me) && ob->query_data(x, y, "south") && dir == "south"
        || userp(me) && ob->query_data(x, y, "west") && dir == "west"
        || userp(me) && ob->query_data(x, y, "east") && dir == "east" ) {

        message_vision("流沙將$N衝了回來！\n", me);
        return 0;
    }
    return ::valid_leave(me, dir);
}
void init()
{
    add_action("do_climb", "climb");
    add_action("do_down", "down" );
}
int do_climb(string arg)
{
    object me, area;
    string area_file = "/world/area/sand_hole/sand.c";

    me = this_player();

    if( me->is_busy() ) return notify_fail("你現在正在忙，一時之間無法移動。\n");
    if( !arg ) return 0;
    if( arg != "樹根" && arg != "根" && arg != "樹" ) return 0;
    if( me->query("area_info/x_axis") != 15 || me->query("area_info/y_axis") != 15 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N抓住了樹根，身手敏捷的穿過沙土爬了上去。\n", me);
    if( !area_move(area, me, 15, 15) ) return 0;
    return 1;
}
int do_down(string arg)
{
    int x, y;
    object me, area;
    string area_file = "/world/area/sand_hole/hole_2b.c";

    me = this_player();
    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( me->is_busy() ) return notify_fail("你現在正在忙，一時之間無法移動。\n");

    if( !userp(me) || !this_object()->query_data(x, y, "cord_down") ) return notify_fail("這個方向沒有出路。\n");

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N在手上吐了口口水，抓住繩頭溜了下去。\n", me);
    if( !area_move(area, me, x, y) ) return 0;
    return 1;
}
