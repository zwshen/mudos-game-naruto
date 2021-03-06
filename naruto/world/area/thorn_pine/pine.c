// (15,0) 入   (8,29) 出

inherit AREA;
#include <ansi.h>

void create()
{
    set("name", "刺松林");
    set("x_axis_size", 30);            // 橫向大小
    set("y_axis_size", 30);            // 縱向大小
    setup();
}
int valid_leave(object me, string dir)
{
    int x, y, i, damage;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    i = random(10)+1;
    damage = random(26)+5;

    if( userp(this_player()) ) {
        if( i < 2) {
            message_vision("$N"HIR"走路不小心，被一旁的尖刺刺傷了！"NOR"("HIY+damage+NOR")\n"NOR, this_player());
            this_player()->damage_stat("hp", damage, this_player());
            this_player()->start_busy(1);
            return 1;
        }
    }
    // return 0; 表示移動失敗
    if( !userp(me) && x == 15 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 14 && y == 1 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 16 && y == 1 && dir == "northwest" ) return 0;
    if( !userp(me) && x == 8 && y == 28 && dir == "south" ) return 0;
    if( !userp(me) && x == 7 && y == 28 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 9 && y == 28 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 12 && y == 12 && dir == "south" ) return 0;
    if( !userp(me) && x == 12 && y == 12 && dir == "southeast" ) return 0;
    return ::valid_leave(me, dir);
}
