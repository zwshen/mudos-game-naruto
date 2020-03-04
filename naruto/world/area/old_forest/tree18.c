#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","古森枝部");

    set("long", @long
這裡是土著們休息的地方，一張用樹根搭成的小桌上放著大片樹
葉的碗裝水。但是他們沒有心情去喝，因為入侵者已經出現了。
long);
    set("exits", ([
        "west" : __DIR__"tree17.c",
        "east" : __DIR__"tree19.c",
    ]));
    set("objects", ([
        __DIR__"npc/warrior.c" : 1,
        __DIR__"npc/shooter.c" : 1,
    ]));
    setup();
}
