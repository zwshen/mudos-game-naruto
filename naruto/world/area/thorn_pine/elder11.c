inherit ROOM;

void create()
{
        set("short", "二樓走道");
        set("long", @LONG
走廊上沒有任何的佈置，只有一扇窗戶透著外面的陽光，照亮這
片並不寬大的走廊，可以看到後面還有一小塊空地，有位豹人正安靜
的坐在搖椅上，發出木頭壓迫的聲音。
LONG);
    set("exits", ([
        "east" : __DIR__"elder10.c",
        "west" : __DIR__"elder12.c",
    ]));
        setup();
}
