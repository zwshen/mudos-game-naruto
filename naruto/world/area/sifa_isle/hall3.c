#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "艾尼艾斯二樓走廊");
    set("long", @LONG
艾尼艾斯大廳二樓的走道，走道上有六間屋子。
LONG);

    set("exits", ([
        "west" : __DIR__"hall2.c",
        "east" : __DIR__"hall4.c",
        "north" : __DIR__"house3.c",
        "south" : __DIR__"house4.c",
    ]));
    setup();
}