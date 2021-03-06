inherit AREA;

void create()
{
    set("name", "陰影小徑");
    set("x_axis_size", 20);            // 橫向大小
    set("y_axis_size", 40);            // 縱向大小
    setup();
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 7 && y == 38 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 8 && y == 38 && dir == "south" ) return 0;
    if( !userp(me) && x == 9 && y == 38 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 13 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 3 && y == 19 && dir == "west" ) return 0;
    if( !userp(me) && x == 1 && y == 21 && dir == "north" ) return 0;
    if( !userp(me) && x == 15 && y == 23 && dir == "north" ) return 0;
    if( !userp(me) && x == 17 && y == 21 && dir == "west" ) return 0;
    return ::valid_leave(me, dir);
}
