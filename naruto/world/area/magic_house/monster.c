#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "獸欄");
    set("long", @LONG

巨大鐵柵欄的大籠子，鐵柵欄似乎是用機關開啟的，你打不開。

LONG);
    set("exits", ([
        "south" : ([ "filename": __DIR__"house.c",
                    "x_axis": 9,
                    "y_axis": 7,
                 ]),
    ]));
    set("objects", ([
        __DIR__"npc/clemens.c" : 1,
    ]));
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_move", "move");
    add_action("do_move", "sfly");
}
int do_move(string arg)
{
    message_vision("$N企圖飛上天空，但是撞到房頂又跌了下來。\n", this_player());
    return 1;
}
