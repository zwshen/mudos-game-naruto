#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "宴會廳");
    set("long", @long
十分寬廣的大室，上面有個用金屬雕刻的牌子刻著「宴會廳」
三個字，大概是這主人舉辦活動時候所用的會場吧。地上到處都是
磁器的碎片或是生鏽的古玩，如果完好無缺的話想必會值很多的錢
吧，真的是非常可惜。
long);
    set("exits", ([
        "west" : ([ "filename": __DIR__"relice.c",
                      "x_axis": 6,
                      "y_axis": 3,
                 ]),
        "east" : __DIR__"banquet2.c",
        "south" : __DIR__"banquet3.c",
        "north" : __DIR__"banquet4.c",
    ]));
    setup();
}
