#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "酒吧房間");
    set("long", @LONG
房間內佈置的像一間酒吧，不過一個客人也沒有。在櫃台有一個
高大男人正在擦拭桌面，也許能跟他問點什麼事吧。
LONG);
    set("exits", ([
        "south" : __DIR__"hall2.c",
    ]));
    set("objects", ([
        __DIR__"npc/bruno.c" : 1,
    ]));
    setup();
}
