inherit AREA;

void create()
{
    set("name", "海底");
    set("x_axis_size", 50);            // 橫向大小
    set("y_axis_size", 50);            // 縱向大小
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

    if( !userp(me) && x == 26 && y == 1 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 27 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 28 && y == 1 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
