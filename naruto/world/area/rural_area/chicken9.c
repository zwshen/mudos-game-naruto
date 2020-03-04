#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "雞舍");
    set("long", @LONG
養雞的屋子，剛走進來就聞到一股很重的雞屎味。屋子中似乎沒
有做任何的防備，有不少的雞都已經跑到外面去了，只剩少數幾隻比
較懶散的雞還在睡覺。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"area.c",
                       "x_axis" : 18,
                       "y_axis" : 8,
                  ]),
        "east" : __DIR__"chicken0.c",
        "north" : __DIR__"chicken4.c",
        "west" : __DIR__"chicken8.c",
    ]));
    setup();
}
