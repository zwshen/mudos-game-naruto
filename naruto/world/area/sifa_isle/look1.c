#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "瞭望台一樓");
    set("long", @LONG
狹窄的空間...旁邊有路可以通往二樓
LONG);

    set("exits", ([
        "up" : __DIR__"look2.c",
        "south" : ([ "filename" : __DIR__"sifa.c",
                     "x_axis" : 45,
                     "y_axis" : 38,
                 ]),
    ]));
    setup();
}
