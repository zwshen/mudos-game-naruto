/* write by -Acme- */

inherit ROOM;

void create()
{
    set("short", "奈良家");

    set("long", @long
這裡是木葉村的奈良家。
long);

    set("exits", ([
        "north" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 17,
                      "y_axis": 20,
                 ]),
    ]));

    setup();
}
