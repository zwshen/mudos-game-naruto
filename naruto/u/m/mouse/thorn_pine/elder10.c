inherit ROOM;

void create()
{
        set("short", "加加辫");
        set("long", @LONG
兵硄┕加加辫芔
LONG);
    set("exits", ([
        "west" : __DIR__"elder11.c",
        "down" : __DIR__"elder03.c",
    ]));
        setup();
}
