#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","土著村");

    set("long", @long
這裡似乎就是土著的村子了，不過因為外來者的入侵，除了戰士
之外找不到婦女、老人和小孩。
long);
    set("exits", ([
        "west" : __DIR__"tree34.c",
        "east" : __DIR__"tree36.c",
    ]));
    set("objects", ([
    __DIR__"npc/shooter.c" : 1,
        __DIR__"npc/warrior.c" : 2,
    ]));
    setup();
}
