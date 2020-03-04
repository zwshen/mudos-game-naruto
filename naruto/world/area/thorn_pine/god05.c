inherit ROOM;

void create()
{
        set("short", "神壇火堆");
        set("long", @LONG
豹人們都坐在地上休息著，有在聊天、有聽神壇上唱歌、也有的
已經睡著了，大家看起來都很輕鬆，不像平常在路上看到的豹人那樣
神情緊繃，也許牠們只有在這裡才能自在的放鬆心情吧。
LONG);
    set("exits", ([
        "west" : __DIR__"god04.c",
        "south" : __DIR__"god07.c",
    ]));
    set("objects", ([
        __DIR__"npc/man.c" : 1,
        __DIR__"npc/woman.c" : 1,
        __DIR__"npc/child.c" : 1,
    ]));
    setup();
}
