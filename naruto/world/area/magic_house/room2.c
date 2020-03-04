#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "柴房");
    set("long", @LONG
裝了很多薪火類的東西，除了馬戲團的動物們天氣寒冷時需要用
來取暖，平時馬戲團的很多表演也會用到這裡的薪火。現在只有一位
年老的馬戲團員在裡面默默地整理材料，看他一把年紀，誰也想不到
以前他也曾是轟動一時的馬戲團明星。
LONG);
    set("exits", ([
        "north" : ([ "filename" : __DIR__"house.c",
                       "x_axis" : 37,
                       "y_axis" : 24,
                  ]),
    ]));
    set("objects", ([
        __DIR__"npc/torre.c" : 1,
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
