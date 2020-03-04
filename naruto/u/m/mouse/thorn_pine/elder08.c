inherit ROOM;

void create()
{
        set("short", "一樓大廳");
        set("long", @LONG
正面的牆上掛了一幅很長的畫，這裡所掛只是畫的中半部而已，
畫中所繪是一位身材高大的豹人，牠手拿著一把金色的巨斧，面目兇
惡的追著前方的一群蜘蛛。
LONG);
    set("exits", ([
        "west" : __DIR__"elder07.c",
        "east" : __DIR__"elder09.c",
        "north" : __DIR__"elder05.c",
    ]));
    set("objects", ([
        __DIR__"npc/man.c" : 1,
        __DIR__"npc/master.c" : 1,
    ]));
    setup();
}
