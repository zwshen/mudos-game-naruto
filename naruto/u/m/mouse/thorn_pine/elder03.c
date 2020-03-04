inherit ROOM;

void create()
{
        set("short", "一樓樓梯");
        set("long", @LONG
一條通往樓上的樓梯，從上面偶爾會傳來木頭壓迫的聲音。
LONG);
    set("exits", ([
        "west" : __DIR__"elder01.c",
        "up" : __DIR__"elder10.c",
        "south" : __DIR__"elder06.c",
    ]));
        setup();
}
