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
    object me, area;
    string area_file = "/world/area/ship/sunmoon.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "錨" ) return 0;

    if( me->query("area_info/x_axis") != 14 || me->query("area_info/y_axis") != 24 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N踏準了錨的鈍處，快速地爬了上去。\n", me);
    if( !area_move(area, me, 9, 25) ) return 0;
    message_vision("$N從海底爬了上來，一臉狼狽。\n", me);
    return 1;
}
