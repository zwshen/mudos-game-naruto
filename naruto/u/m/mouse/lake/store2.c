#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "倉庫內");
    set("long", @long
四周黑漆漆的讓人看不清楚，但總讓人覺得好像有東西在盯著
你看，當你點亮了手中光源後，差點沒吐了出來。只見一具全身腐
爛的屍體正拖著沉重的步伐走來，似乎沒什麼善意。
long);
    set("exits", ([
        "west" : __DIR__"store.c",
        "east" : __DIR__"store3.c",
        "north" : __DIR__"store4.c",
    ]));
    set("objects", ([
    __DIR__"npc/zombie.c" : 1,
    ]));
    setup();
}
