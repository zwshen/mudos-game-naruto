#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "右側二樓");
    set("long", @LONG
樓梯一直往上延伸...暫時還看不到頂端。
LONG);
    set("exits", ([
        "up" : __DIR__"right3.c",
        "down" : __DIR__"right1.c",
    ]));
    setup();
}
