#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "猿山連合屋貳樓");
        set("long", @LONG
房間的牆壁比其他房間都還要厚，不知道是什麼原因才把這裡的
隔音效果做的那麼好？房門上寫著「探索王」猩猩。
LONG);
    set("exits", ([
        "up" : __DIR__"monkey3.c",
        "down" : __DIR__"monkey1.c",
        "east" : ([ "filename" : __DIR__"lufi.c",
                       "x_axis" : 26,
                       "y_axis" : 24,
                  ]),

    ]));
    setup();
}
