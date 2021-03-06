#include <ansi.h>

inherit AREA;

string *gowhere = ({ "go north", "go south", "go east", "go west",
                     "go northeast", "go northwest", "go southeast", "go southwest" });

void create()
{
    set("name", "死亡城內");
    set("x_axis_size", 31);            // 橫向大小
    set("y_axis_size", 31);            // 縱向大小
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_fling", "fling");
    add_action("do_climb", "climb");
}
int do_fling(string arg)
{
    object me, obj, mob;
    int x, y, i, j;

    me = this_player();
    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( userp(me) && x == 25 && y == 27 ) {

        if( !arg ) return notify_fail("你想要丟什麼東西？\n");
        if( me->is_busy() ) return notify_fail("你正在忙碌中，不能動作。\n");
        if( !objectp(obj = present(arg, me))) return notify_fail("你身上沒有這樣東西。\n");
        if( obj->query("no_drop") ) return notify_fail("這樣東西不能隨意丟棄。\n");
        if( obj->query("keep_this") ) return notify_fail("這樣東西你已經 keep 無法丟棄。\n");
        if( obj->query("equipped") ) return notify_fail("這樣東西你已經裝備著，無法丟棄。\n");

        if( obj->query("name") == HIM"魂"HIC"玉"NOR ) {

            i = random(5) + 1;

            message_vision("$N將"+obj->query("name")+"丟進地洞中，四周忽然震動了起來，好像看見"+chinese_number(i)+"道黑影竄出！\n"NOR, me);

            if( !obj->query_amount() ) destruct(obj);
            else obj->add_amount(-1);

            for(j=0;j<=i;j++) {
                mob = new(__DIR__"npc/mindflayer.c");
                area_move(environment(me), mob, 1+random(29), 1+random(23));
            }
        } else {
            message_vision("$N將"+obj->query("name")+"丟進地洞中，但是沒發生任何事。\n"NOR, me);
            if( !obj->query_amount() ) destruct(obj);
            else obj->add_amount(-1);
        }
        me->start_busy(2);
        return 1;
    }
    return 0;
}
int do_climb(string arg)
{
    object me, area;
    string area_file = "/world/area/lv60_area/deadsite.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "繩子" && arg != "繩頭" ) return 0;
    if( me->query("area_info/x_axis") != 27 || me->query("area_info/y_axis") != 25 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N拉起繩子綁在身上，腳踏牆壁爬了上去。\n", me);
    if( !area_move(area, me, 24, 36) ) return 0;
    message_vision("$N從旁邊的小縫鑽了出來。\n", me);
    return 1;
}
int valid_leave(object me, string dir)
{
    object ob;
    int x, y;

    if( !me ) return 0;

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    ob = this_object();

    if( userp(me) && ob->query_data(x, y, "move") && random(100) < 60 && !me->query_temp("gowhere")) {
        me->add_temp("gowhere", 1);
        me->force_me(gowhere[random(sizeof(gowhere))]);
        me->force_me(gowhere[random(sizeof(gowhere))]);
        me->delete_temp("gowhere");
        message_vision(HIW"$N迷失了神智...居然自己到處亂跑...\n"NOR, me);
        return 1;
    }
    return ::valid_leave(me, dir);
}
