inherit AREA;

void create()
{
    set("name", "海底");
    set("x_axis_size", 50);            // 橫向大小
    set("y_axis_size", 50);            // 縱向大小
    setup();
}
void init()
{
    add_action("do_climb", "climb");
}
int do_climb(string arg)
{
    string area_file = "/world/area/whale_island/area.c";
    object me, area;
    int x, y;

    me = this_player();
    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( !arg ) return 0;
    if( arg != "魚勾" ) return 0;

    if( x == 19 && y == 0 || x == 20 && y == 0 ||
        x == 21 && y == 0 || x == 22 && y == 0 ) {

        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        message_vision("$N用力抓住魚線，把釣魚人扯下海後自己爬了上去。\n", me);
        if( !area_move(area, me, 22, 45+random(3)) ) return 0;
        message_vision("$N從海裡爬了上來。\n", me);
        return 1;
    }
    return 0;
}
int valid_leave(object me, string dir)
{
    string area_file = "/world/area/benthal/sea5.c";
    object ob, area;
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    ob = this_object();

    if( x == 2 && y == 47 && dir == "south" || 
        x == 2 && y == 47 && dir == "southwest" ) {

        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        if( !userp(me) ) return 0;
        message_vision("海流突然將$N捲了進去！連意志也被拉走了...\n", me);
        if( !area_move(area, me, 43+random(7), 8+random(7)) ) return 0;
        message_vision("$N被海流衝到這裡才醒過來，不明的海域。\n", me);
        return 1;
    }
    return ::valid_leave(me, dir);
}
