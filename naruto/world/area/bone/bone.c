#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "骸骨戰場");
    set("x_axis_size", 41);            // 橫向大小
    set("y_axis_size", 41);            // 縱向大小
    setup();
    set("no_recall", 1);
}
void init()
{
    object me = this_player();

    // muye的會扣比較多
    if( me->hasCamp("music") == 0 && this_player()->query("guild") == "muye" ) {
        tell_object(me,HIR"這裡是對木葉敵意非常深的音隱忍者領地...\n"NOR);
        me->setCamp("music", -60000);
    } else if( me->hasCamp("music") == 0 ) {
        tell_object(me,HIR"音之忍者對於你似乎充滿了敵對心態。\n"NOR);
        me->setCamp("music", -35000);
    }
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 5 && y == 39 && dir == "southeast" ) return 0;
    if( !userp(me) && x == 6 && y == 39 && dir == "south" ) return 0;
    if( !userp(me) && x == 7 && y == 39 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 5 && y == 40 && dir == "east" ) return 0;
    if( !userp(me) && x == 7 && y == 40 && dir == "west" ) return 0;
    if( !userp(me) && x == 1 && y == 6 && dir == "west" ) return 0;
    if( !userp(me) && x == 1 && y == 5 && dir == "southwest" ) return 0;
    if( !userp(me) && x == 1 && y == 7 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
