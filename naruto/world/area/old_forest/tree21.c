#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","古森枝部");

    set("long", @long
地上堆滿了樹枝和樹葉，不知道是做什麼用的。
long);
    set("exits", ([
        "west" : __DIR__"tree20.c",
    ]));
    setup();
}
