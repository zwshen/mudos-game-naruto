#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", HIR"阿基的家"NOR);
    set("long", @LONG
很普通的家，唯一特別的地方就是所有的家具都是紅色的，不知
是對紅色有特殊僻好還是什麼其他的原因？
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"area.c",
                       "x_axis" : 31,
                       "y_axis" : 17,
                  ]),
    ]));
    set("objects", ([
        __DIR__"npc/gi.c" : 1,
    ]));
    setup();
}
