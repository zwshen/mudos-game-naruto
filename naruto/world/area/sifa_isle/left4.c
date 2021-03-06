#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "左側頂樓");
    set("long", @LONG
頂樓有一扇窗戶透著光芒進來，只見眼前是一個大型的機關，不
知道有什麼用，不過你想去碰這個機關也沒那麼簡單，有個身穿和服
的怪人正擋在機關前面。
LONG);
    set("exits", ([
        "down" : __DIR__"left3.c",
    ]));
    set("detail", ([
        "機關": "似乎可以推動(push)的樣子。",
    ]));
    set("objects", ([
        __DIR__"npc/wei.c" : 1,
    ]));
    setup();
}
void init()
{
    add_action("do_push", "push");
}
int do_push(string arg)
{
    object ob, me;
    
    me = this_player();

    if( arg == "機關" ) {
        if( ob = present("_WEI_", environment(me)) ) {
            message_vision(ob->query("name")+"說道："HIG"呦伊呦伊！既然...敢動機關！...\n"NOR, me);
            message_vision(ob->query("name")+"說道："HIG"那$N就...下黃泉去吧！\n"NOR, me);
            message_vision(ob->query("name")+"說道："HIG"順便告訴我已逝的母親！...我過的很好！呦伊呦伊！\n"NOR, me);
            ob->kill_ob(me);
            me->kill_ob(ob);
            return 1;
        } else {
            me->add_temp("quest/justdoor", 1);
            message_vision("$N用力的將機關推進去。\n", this_player());
            message_vision(CYN"只見後方的吊橋好像因此放下來了一些。\n"NOR, this_player());
            return 1;
        }
    }
    return notify_fail("你推動什麼？\n");
}
