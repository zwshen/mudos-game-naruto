#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "庭院房間");
    set("long", @LONG
房間內佈置的像個庭院，有涼亭和流水，還有小橋與一群小動物
，看起來很和諧的樣子。在房子的正中間有一個男子，正趴在地上睡
覺，只見他的身旁放著一袋看起來好像很重的袋子，袋子上還寫個大
大的「錢」字，該不會是錢袋吧。
LONG);
    set("exits", ([
        "north" : __DIR__"hall2.c",
    ]));
    set("detail", ([
        "錢袋": "看起來很重的樣子，起碼有幾斤重，想拿(get)嗎？。",
    ]));
    set("objects", ([
        __DIR__"npc/jia.c" : 1,
    ]));
    setup();
}
void init()
{
    add_action("do_get", "get");
}
int do_get(string arg)
{
    object ob, me;
    
    me = this_player();

    if( arg == "錢袋" ) {
        if( ob = present("_JIA_", environment(me)) ) {
            message_vision(ob->query("name")+"忽然睜開了眼睛。\n"NOR, me);
            message_vision(ob->query("name")+"說道："HIG"哈哈哈！有小魚上勾了！\n"NOR, me);
            message_vision(ob->query("name")+"說道："HIG"搶奪海軍財物！去死吧！\n"NOR, me);
            ob->kill_ob(me);
            me->kill_ob(ob);
            return 1;
        } else {
            message_vision("$N拿起了錢袋，卻發現裡面都是不值錢的重物。\n", this_player());
            return 1;
        }
    }
}
