inherit ROOM;

void create()
{
    set("short", "燒賣小吃店");

    set("long", @long
這裡是鯨魚島上唯一一家專門賣燒賣的小吃店。
long);

    set("exits", ([
        "east" : ([ "filename": __DIR__"area.c",
                      "x_axis": 15,
                      "y_axis": 18,
                 ]),
    ]));

    set("objects", ([
        __DIR__"npc/snack_boss" : 1,
    ]));

    setup();
}


