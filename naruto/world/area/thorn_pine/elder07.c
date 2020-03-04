inherit ROOM;

void create()
{
        set("short", "一樓大廳");
        set("long", @LONG
正面的牆上掛了一幅很長的畫，這裡所掛只是畫的左半部而已，
畫中所繪是一群身穿動物毛皮的豹人，牠們手持長槍巨斧，好像在追
趕著什麼東西的樣子。
LONG);
    set("exits", ([
        "east" : __DIR__"elder08.c",
        "north" : __DIR__"elder04.c",
    ]));
    set("objects", ([
        __DIR__"npc/warrior.c" : 1,
        __DIR__"npc/master.c" : 1,
    ]));
    setup();
}
