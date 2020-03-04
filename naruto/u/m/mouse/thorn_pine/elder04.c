inherit ROOM;

void create()
{
        set("short", "一樓大廳");
        set("long", @LONG
周圍擺放著用樹幹做成的椅子和桌子，上面鋪著動物的毛皮顯得
十分舒適，桌子上則放著一些器具。
LONG);
    set("exits", ([
        "east" : __DIR__"elder05.c",
        "north" : __DIR__"elder02.c",
        "south" : __DIR__"elder07.c",
    ]));
    set("objects", ([
        __DIR__"npc/warrior.c" : 1,
        __DIR__"npc/master.c" : 1,
    ]));
    setup();
}
