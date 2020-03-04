#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "練習場(８)");
        set("long", @LONG
這裡擺放了幾個假人，可以在這裡練技格鬥技能。
LONG);

        set("exits", ([
        "south" : ([ "filename" : __DIR__"area.c",
                     "x_axis" : 25,
                     "y_axis" : 20,
                  ]),           
                "north" : __DIR__"prac5",               
                "west" : __DIR__"prac7",                
                "east" : __DIR__"prac9",                
        ]));

    set("objects", ([
        _DIR_NPC_"stake.c": 4,
    ]));

        setup();
}
