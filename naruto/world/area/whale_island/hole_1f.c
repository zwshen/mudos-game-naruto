inherit AREA;

void create()
{
    set("name", "陰影巢穴-B1");
    set("x_axis_size", 20);            // 橫向大小
    set("y_axis_size", 20);            // 縱向大小
    setup();
}

int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 0 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 5 && y == 1 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 6 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 7 && y == 1 && dir == "northwest" ) return 0;
    if( !userp(me) && x == 18 && y == 6 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 18 && y == 7 && dir == "east" ) return 0;
    if( !userp(me) && x == 18 && y == 8 && dir == "northeast" ) return 0;
    return ::valid_leave(me, dir);
}
