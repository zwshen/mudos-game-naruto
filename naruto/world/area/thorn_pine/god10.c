inherit ROOM;

void create()
{
        set("short", "神壇火堆");
        set("long", @LONG
豹人們高興的在火堆的四周跳著舞，牠們的雙手快速的變換著手
勢，腳步也沒有停止，不停的左右跳動變化節奏。看起來就像是在訓
練快速移動與靈活的運手雙手，將訓練融入生活之中。
LONG);
    set("exits", ([
        "north" : __DIR__"god08.c",
        "south" : __DIR__"god12.c",
    ]));
    set("objects", ([
        __DIR__"npc/man.c" : 1,
        __DIR__"npc/woman.c" : 1,
    ]));
    setup();
}
