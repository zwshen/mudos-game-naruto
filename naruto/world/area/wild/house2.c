#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "臥房");
    set("long", @LONG
一間堆滿了補蛇器具的小臥房，看起來相當的雜亂
LONG);

    set("exits", ([
        "west" : __DIR__"house.c",
    ]));

    set("objects", ([
        __DIR__"npc/wan.c" : 1,
    ]));

    setup();
}

