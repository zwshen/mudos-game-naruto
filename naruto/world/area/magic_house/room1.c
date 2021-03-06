#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "團員休息室");
    set("long", @LONG
看似簡單的小房間，卻能讓一位馬戲團團員做好萬全的準備，各
式各樣的化裝用品一樣也不能少，還有冰箱提供團員們享受清涼的冷
飲。房間中央一面巨大的鏡子能夠讓團員確認自己的準備是否已經完
成，然後充滿著信心去面對客人們。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"house.c",
                       "x_axis" : 37,
                       "y_axis" : 24,
                  ]),
    ]));
    set("objects", ([
        __DIR__"npc/johnson.c" : 1,
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
