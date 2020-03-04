inherit ROOM;

void create()
{
    set("short", "冶金廠");
    set("long", @long
火紅的房間中有位打著赤膊地壯漢，有事可以問他。
long);
    set("exits", ([
        "east" : ([ "filename": __DIR__"wizard.c",
                      "x_axis": 5,
                      "y_axis": 44,
                 ]),
        "west" : __DIR__"found.c",
    ]));
    set("objects", ([
        __DIR__"npc/founder.c" : 1,
    ]));
    setup();
}
