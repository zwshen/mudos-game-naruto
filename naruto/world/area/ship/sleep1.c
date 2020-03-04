#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "┬");
        set("long", @LONG
┬加娩Τ加辫加┬加弧虏ぃ
虏Τ碭眎ㄤ狥﹁ぐ或⊿Τ
LONG);
    set("exits", ([
        "down" : __DIR__"sleep2.c",
        "south" : ([ "filename" : __DIR__"lufi.c",
                       "x_axis" : 9,
                       "y_axis" : 15,
                  ]),
    ]));
    setup();
}
