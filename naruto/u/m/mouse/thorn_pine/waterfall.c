inherit AREA;

void create()
{
    set("name", "轟天瀑");
    set("x_axis_size", 21);            // 橫向大小
    set("y_axis_size", 41);            // 縱向大小
    setup();
}
void init()
{
    add_action("do_jump", "jump");
    add_action("do_climb", "climb");
}
int do_jump(string arg)
{
    object me, area;
    string area_file = __DIR__"waterfall.c";
    me = this_player();

    if( !arg ) return 0;
    if( arg != "瀑布") return 0;

    if( me->query("area_info/y_axis") != 11 ) return 0;
    if( (me->query("area_info/x_axis") == 7) || (me->query("area_info/x_axis") == 8)  ||
        (me->query("area_info/x_axis") == 9) || (me->query("area_info/x_axis") == 10) ||
        (me->query("area_info/x_axis") == 11)|| (me->query("area_info/x_axis") == 12) ||
        (me->query("area_info/x_axis") == 13) ) {

        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        if( !(userp(me)) ) {
            message_vision("$N捏著鼻子，閉上眼睛往瀑布跳了下去。\n", this_player());
            if( !area_move(area, me, 7+random(7), 26) ) return 0;
            message_vision("$N從瀑布上一路滾了下來，痛的哇哇大叫。\n", this_player());
            return 1;
        }
        message_vision("$N捏著鼻子，閉上眼睛往瀑布跳了下去。\n", this_player());
        if( !area_move(area, me, 7+random(7), 27+random(5)) ) return 0;
        message_vision("$N睜開眼睛才發現自己已經掉落到瀑布下端了。\n", this_player());
        return 1;
    }
    return 0;
}

int do_climb(string arg)
{
    object me, area;
    string area_file = __DIR__"waterfall.c";
    me = this_player();

    if( !arg ) return 0;
    if( arg != "瀑布") return 0;

    if(me->is_busy()) {
        tell_object(me, "你正在忙碌，沒空爬瀑布。\n");
        return 1;
    }
    if( me->query("area_info/y_axis") != 26 ) return 0;
    if( (me->query("area_info/x_axis") == 7) || (me->query("area_info/x_axis") == 8)  ||
        (me->query("area_info/x_axis") == 9) || (me->query("area_info/x_axis") == 10) ||
        (me->query("area_info/x_axis") == 11)|| (me->query("area_info/x_axis") == 12) ||
        (me->query("area_info/x_axis") == 13) ) {

        if( random(me->query_ability("evade")) <= 100) { 
            message_vision("$N試圖爬上瀑布，但是被水衝了下來！\n", this_player());
            me->damage_stat("ap", 10, me);
            me->start_busy(2);
            return 1;
        }
        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        message_vision("$N快速的爬上瀑布，在水壓下仍然緩緩前進。\n", this_player());
        if( !area_move(area, me, random(7)+7, 11) ) return 0;
        message_vision("$N吐了一口氣，終於游到瀑布上端了。\n", this_player());
        return 1;
    }
    return 0;
}
int valid_leave(object me, string dir)
{
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( !userp(me) && x == 18 && y == 1 && dir == "north" ) return 0;
    if( !userp(me) && x == 17 && y == 1 && dir == "northeast" ) return 0;
    if( !userp(me) && x == 19 && y == 1 && dir == "northwest" ) return 0;

    return ::valid_leave(me, dir);
}
