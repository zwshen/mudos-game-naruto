inherit AREA;

void create()
{
    set("name", "戰事林");
    set("x_axis_size", 41);            // 橫向大小
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
    if( !userp(me) && x == 39 && y == 8 && dir == "east" ) return 0;
    if( !userp(me) && x == 39 && y == 9 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 10 && y == 11 && dir == "north" ) return 0;
    if( !userp(me) && x == 9 && y == 11 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 2 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 3 && y == 1 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
