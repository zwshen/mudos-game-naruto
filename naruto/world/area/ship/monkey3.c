#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "猿山連合屋參樓");
        set("long", @LONG
房間裡掛著許多的照片，照片中是猩猩和猿人與一個頭上有栗子
的菱形臉大叔的合照，有日常的生活還有找到寶物時的照片。照片中
三人都笑的十分開心。
LONG);
    set("exits", ([
        "down" : __DIR__"monkey2.c",
        "east" : ([ "filename" : __DIR__"lufi.c",
                       "x_axis" : 26,
                       "y_axis" : 22,
                  ]),

    ]));
    setup();
}
