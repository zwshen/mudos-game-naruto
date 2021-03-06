inherit AREA;

void create()
{
    set("name", "精靈之屋");
    set("x_axis_size", 31);            // 橫向大小
    set("y_axis_size", 31);            // 縱向大小
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_quit", "quit");
    add_action("do_fly", "sfly");
    add_action("do_fly", "move");
}
int do_quit(string arg)
{
    tell_object(this_player(),"\n因為神奇的力量，你的離線行為僅被移置門外。\n\n");
    this_player()->move(__DIR__"elf_door.c");
    this_player()->start_busy(1);
    return 1;
}
int do_fly(string arg)
{
    tell_object(this_player(),"這裡充滿奇特的能源，使你的飛行道具失靈了。\n");
    return 1;
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    // return 0; 表示移動失敗
    if( !userp(me) && x == 15 && y == 17 && dir == "north" ) return 0;
    if( !userp(me) && x == 14 && y == 17 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 16 && y == 17 && dir == "northwest" ) return 0;
    if( userp(me) && x == 15 && y == 17 && dir == "north" ) me->delete_temp("ELF_HOUSE");
    return ::valid_leave(me, dir);
}
