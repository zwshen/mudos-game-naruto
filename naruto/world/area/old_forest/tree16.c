#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","古森枝部");

    set("long", @long
少數的土著正在在裡不停的徘徊著，他們神情緊繃、面色凝重，手拿
著武器隨時保持攻擊的姿態。
long);
    set("exits", ([
        "west" : __DIR__"tree15.c",
        "east" : __DIR__"tree17.c",
        "northeast" : __DIR__"tree10.c",
    ]));
    set("objects", ([
        __DIR__"npc/warrior.c" : 1,
    ]));
    setup();
}
