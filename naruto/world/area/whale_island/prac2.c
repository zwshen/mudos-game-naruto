#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "練習場(２)");
        set("long", @LONG
這裡擺放了幾個假人，可以在這裡練技格鬥技能。
LONG);

        set("exits", ([
        "north" : ([ "filename" : __DIR__"area.c",
                     "x_axis" : 25,
                     "y_axis" : 14,
                  ]),           
                "west" : __DIR__"prac1",
                "south" : __DIR__"prac5",
                "east" : __DIR__"prac3",
        ]));

    set("objects", ([
        _DIR_NPC_"stake.c": 4,
    ]));

        setup();
}
