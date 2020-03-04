#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "作戰室");
        set("long", @LONG
房中間放了一張大圓桌，桌上擺了一張這附近的地圖。地圖上在
木葉忍者村的四周畫滿了各種的符號，難道他們正在計劃攻擊木葉忍
者村嗎？還好四周忍者都忙著自己的事，沒發現有人在偷看地圖。
LONG);
    set("exits", ([
        "east" : __DIR__"home04.c",
        "west" : __DIR__"home02.c",
        "south" : __DIR__"home06.c",
    ]));
    setup();
}
