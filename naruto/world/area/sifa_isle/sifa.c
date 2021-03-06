#include <ansi.h>
inherit AREA;

void create()
{
    set("name", "司法島");
    set("x_axis_size", 90);            // 橫向大小
    set("y_axis_size", 100);           // 縱向大小
    setup();
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 44 && y == 26 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 45 && y == 26 && dir == "north" ) return 0;
    if( !userp(me) && x == 46 && y == 26 && dir == "northwest" ) return 0;
    return ::valid_leave(me, dir);
}
void init()
{
    object me = this_player();

    add_action("do_jump", "jump");
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
int do_jump(string arg)
{
    object me, area;
    string area_file = "/world/area/benthal/sea1.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "海" && arg != "海岸" && arg != "汪洋大海") return 0;

    if( me->query("area_info/x_axis") != 45 || me->query("area_info/y_axis") != 94 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N深深吸了一口氣，捏著鼻子往大海一跳！\n", me);
    if( !area_move(area, me, 25, 0) ) return 0;
    message_vision("$N從海面沉了下來，身旁都是氣泡。\n", me);

    return 1;
}
