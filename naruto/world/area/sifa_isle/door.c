#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", GRN"空氣門"NOR);
    set("long", @LONG
專門為布魯諾設計的小屋子，一般玩家無法進入。
LONG);
    setup();
}
