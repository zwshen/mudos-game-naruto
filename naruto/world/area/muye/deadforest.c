// write by -Acme-

inherit AREA;

void create()
{
    set("name", "死亡森林");
    set("x_axis_size", 49);            // 橫向大小
    set("y_axis_size", 49);            // 縱向大小
    set("no_recall", 1);               //不能使用recall指令
    setup();
}
void init()
{
    add_action("do_pass", "pass");
}
int do_pass(string arg)
{
    object me, area;
    string area_file = "/world/area/lv60_area/deadsite.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "密林" ) return 0;
    if( me->query("area_info/x_axis") != 46 || me->query("area_info/y_axis") != 48 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N努力地將身體擠進空間不大的樹林中。\n", me);
    if( !area_move(area, me, 24, 1) ) return 0;
    message_vision("$N好不容易才擠了進來。\n", me);
    return 1;
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( !userp(me) && x == 5 && y == 3 && dir == "north" ) return 0;

    if( userp(me) && x == 5 && y == 2 && dir == "south" && !me->query_temp("middle_test") ) {
        tell_object(me, "只有參加中忍考試的人才可以進去。\n");
        return 0;
    }

    return ::valid_leave(me, dir);
}
