#include <ansi.h>
inherit AREA;

void create()
{
    set("name", "艾尼艾斯大廳");
    set("x_axis_size", 30);            // 橫向大小
    set("y_axis_size", 30);            // 縱向大小
    setup();
}
void init()
{
    object me = this_player();

    // 因為海賊海軍同屬 piece...所以只好用 class 判斷, 設到二轉應該不會有人漏掉吧
    if( me->hasCamp("robber") == 0 && (this_player()->query_class() == "work_sea" || this_player()->query_class() == "soldier_sea") ) {
        tell_object(me,HIR"受到海軍前輩們的指導，你愈來愈厭惡海賊了。\n"NOR);
        me->setCamp("robber", -34999);
    }
    if( me->hasCamp("police") == 0 && (this_player()->query_class() == "little_sea" || this_player()->query_class() == "thief_sea") ) {
        tell_object(me,HIR"一個海賊居然出現在海軍領地...當然立刻引起了海軍的注意。\n"NOR);
        me->setCamp("police", -34999);
    }
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 14 && y == 28 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 15 && y == 28 && dir == "south" ) return 0;
    if( !userp(me) && x == 16 && y == 28 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 10 && y == 9 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 20 && y == 9 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
