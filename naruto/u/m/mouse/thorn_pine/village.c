// 入(22,0)  出(9,30) (0,12)
inherit AREA;

void create()
{
    set("name", "豹人部落");
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

    if( (userp(me) && x == 20 && y == 18) || (userp(me) && x == 24 && y == 18) ) {
        if( ( dir == "south") ) {

            me->add_temp("quest/villpk", 1);
        } else
            if( ( dir == "northwest") || ( dir == "north") ||
                ( dir == "northeast") ) {

                me->delete_temp("quest/villpk");
        }
        return ::valid_leave(me, dir);
    }
    if( userp(me) && x == 1 && y == 12 && dir == "west" && !me->query_temp("inter_test") ) {
        tell_object(me, "參加有照獵人考試的人才可以進去。\n");
        return 0;
    }
    if( !userp(me) && x == 22 && y == 4 && dir == "north" ) return 0;
    if( !userp(me) && x == 8 && y == 29 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 9 && y == 29 && dir == "south" ) return 0;
    if( !userp(me) && x == 10 && y == 29 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 1 && y == 12 && dir == "west" ) return 0;
    return ::valid_leave(me, dir);
}
