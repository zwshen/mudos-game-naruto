inherit ROOM;

void create()
{
        set("short", "神壇走道");
        set("long", @LONG
這裡是神壇下方圍起來的走道，旁邊圍了一些豹族人正在休息或
是跳舞。神壇上一直傳出永不間斷的歌聲，幾位豹族女性就這樣不停
的輪流上去唱歌。
LONG);
    set("exits", ([
        "east" : ([ "filename" : __DIR__"village.c",
                       "x_axis" : 19,
                       "y_axis" : 12,
                  ]),
        "north" : __DIR__"god07.c",
        "south" : __DIR__"god11.c",
        "west" : __DIR__"altar03.c",
    ]));
    setup();
}
