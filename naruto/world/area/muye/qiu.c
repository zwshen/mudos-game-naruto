/* write by -Acme- */

inherit ROOM;

void create()
{
    set("short", "秋道家");

    set("long", @long
這裡是木葉村的秋道家。
long);

    set("exits", ([
        "north" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 20,
                      "y_axis": 20,
                 ]),
    ]));

    setup();
}
