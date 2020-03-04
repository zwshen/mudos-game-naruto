/* write by -Acme- */

inherit ROOM;

void create()
{
    set("short", "木葉醫藥");

    set("long", @long
這裡是一間專門販賣醫療用品的地方，你可以看見四週陳列了許
許多多的藥品，看起來種類相當齊全，且價格也是十分合理。你又看
見大門口上方掛著一塊血紅色的匾額，上頭寫著「藥到命除」，你不
禁心頭一驚而兩腿發軟。
long);

    set("exits", ([
        "north" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 25,
                      "y_axis": 21,
                 ]),
        "south" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 25,
                      "y_axis": 27,
                 ]),
    ]));

    set("objects", ([
        __DIR__"npc/piller.c": 1,
    ]));

    setup();
}
