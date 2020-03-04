#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "突擊");
        set("long", @LONG
地板上凹凹凸凸的非常不規則，牆上掛了一件黑色的緊身衣還有
一把長刀，兩樣物品的中間用著人類的文字寫著『突』大概可以猜出
這裡是蛇人練習突擊戰術的場地吧。只見牆壁其他地方刻滿了各種圖
案和文字說名，可是文字是用蛇族的字寫的，完全看不懂。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"marsh.c",
                       "x_axis" : 6,
                       "y_axis" : 8,
                  ]),
    ]));
    setup();
}
