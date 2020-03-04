#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "童角的研究室");
        set("long", @LONG
    一間破舊的小屋，裡面有一些治療用的器材。
LONG);
    set("exits", ([
        "east" : ([ "filename" : __DIR__"muye.c",
                       "x_axis" : 11,
                       "y_axis" : 10,
                  ]),
    ]));
    set("objects", ([
        _DIR_AREA_"bone/npc/gau.c" : 1,
        __DIR__"npc/white_eyes_ninja.c": 1,
    ]));
    setup();
}
