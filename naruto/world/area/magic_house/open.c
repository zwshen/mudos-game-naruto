#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "獸欄開關室");
    set("long", @LONG

這個房間裡只有一個開關，旁邊寫著『閒雜人等請勿啟動開關』

LONG);
    set("exits", ([
        "south" : ([ "filename": __DIR__"house.c",
                    "x_axis": 3,
                    "y_axis": 5,
                 ]),
    ]));
    set("detail", ([
        "開關": "似乎可以往裡面推(push)的樣子。",
    ]));
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_push", "push");
    add_action("do_move", "move");
    add_action("do_move", "sfly");
}
int do_move(string arg)
{
    message_vision("$N企圖飛上天空，但是撞到房頂又跌了下來。\n", this_player());
    return 1;
}
int do_push(string arg)
{
    int i, j, x, y;
    object mob, room;

    if( query("MONSTER_WAR") != 0 ) return notify_fail("但是開關已經推進去了。\n");
    if( this_player()->query_level() < 21 ) return notify_fail("你根本沒膽子去啟動開關。\n");
    if( arg == "開關" ) {
        message_vision("$N用力的將開關朝裡面推了進去！\n", this_player());
        message_vision(HIR"只見四周警鈴響起似乎發生了什麼事...\n"NOR, this_player());
        this_player()->start_busy(1);
        set("MONSTER_WAR", 1);
        if( !WAR_D->doStartWar(this_player(), "/world/war/magic_house.c") ) {
            tell_object(this_player(), "開關已經開了，獸欄內空空如也。\n"NOR);
        }
        return 1;
    }
    return notify_fail("你想推什麼東西？\n");
}
