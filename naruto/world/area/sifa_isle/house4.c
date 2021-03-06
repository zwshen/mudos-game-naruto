#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "簡易的房間");
    set("long", @LONG
房間內非常簡陋，除了必要的物品之外幾乎什麼也沒有，房間內
站了一個男子，臉上也是沒有表情，幾乎完全融入這片空間之中，他
似乎也不太在意你的存在，就算你進入了屋子，他也依然一動也不動
的站在原地，應該不會只是蠟像吧。
LONG);
    set("exits", ([
        "north" : __DIR__"hall3.c",
    ]));
    set("objects", ([
        __DIR__"npc/lu.c" : 1,
    ]));
    setup();
}