#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "六芒星陣地");
    set("long", @LONG
你身處於六芒星魔法陣中，感覺全身的力量源源不絕的湧出來，
不過每當你發動攻擊時，卻又感覺全身的力量就像遇到一個深不見底
的旋渦，源源不絕的被吸走，讓你恨不得趕快離開這個奇怪的地方。
只見四周放著許多發著光芒的魔法假人，似乎可以用來練功。
LONG);
    set("exits", ([
        "east" : __DIR__"magic02.c",
        "south" : __DIR__"magic05.c",
    ]));
    set("objects", ([
        __DIR__"npc/item/stake.c" : 3,
    ]));
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_move", "move");
    add_action("do_move", "sfly");
}
int do_move(string arg)
{
    message_vision("$N企圖飛上天空，但是撞到房頂又跌了下來。\n", this_player());
    return 1;
}
