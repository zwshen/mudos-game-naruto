#include <ansi.h>
inherit ROOM;
int i;

void create()
{
    set("short","古森上枝");

    set("long", @long
土著們追到這裡就忽然停住了腳步，慢慢離開了。仔細看看這裡
可以發現，眼前有一棵樹完全看不到頂，只有看到樹幹的部份，旁邊
有五條樹枝往上延伸著，也許是爬上去的路吧。
long);
    set("exits", ([
        "west" : __DIR__"tree29.c",
        "east" : __DIR__"tree31.c",
    ]));
    set("detail", ([
        "樹枝": "五條樹枝延伸到樹到上頭，不清楚會通向哪邊，隨便找一條爬(climb)上去吧。",
    ]));
    setup();
}
void init()
{
    add_action("do_climb", "climb");
}

int do_climb(string arg)
{
    i = random(4);
    if( arg == "樹枝") {
    if(i==1) {
    message_vision("$N抓起其中一根樹枝慢慢爬了上去。\n", this_player());
    this_player()->move(__DIR__"tree13.c");
    message_vision("$N不知道從哪裡爬了過來。\n", this_player());
    return 1;
    }
    else if(i==2) {
    message_vision("$N抓起其中一根樹枝慢慢爬了上去。\n", this_player());
    this_player()->move(__DIR__"tree04.c");
    message_vision("$N不知道從哪裡爬了過來。\n", this_player());
    return 1;
    }
    else if(i==3) {
    message_vision("$N抓起其中一根樹枝慢慢爬了上去。\n", this_player());
    this_player()->move(__DIR__"tree15.c");
    message_vision("$N不知道從哪裡爬了過來。\n", this_player());
    return 1;
    }
    else if(i==4) {
    message_vision("$N抓起其中一根樹枝慢慢爬了上去。\n", this_player());
    this_player()->move(__DIR__"tree27.c");
    message_vision("$N不知道從哪裡爬了過來。\n", this_player());
    return 1;
    }
    else if(i==0) {
    message_vision("$N抓起其中一根樹枝慢慢爬了上去。\n", this_player());
    this_player()->move(__DIR__"oldtree.c");
    message_vision("$N辛苦的爬了上來。\n", this_player());
    return 1;
            }
    }
    return notify_fail("你想爬什麼東西？\n");
}

