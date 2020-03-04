/* write by -Acme- */

inherit ROOM;

void create()
{
    set("short", "愛子家");

    set("long", @long
這裡是木葉村的愛子家。
long);

    set("exits", ([
        "north" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 11,
                      "y_axis": 20,
                 ]),
        "south" : __DIR__"ai2.c",
    ]));

    set("objects", ([
        __DIR__"npc/ai.c" : 1,
    ]));

    setup();
}
