#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "右側頂樓");
    set("long", @LONG
頂樓有一扇窗戶透著光芒進來，只見眼前是一個大型的機關，不
知道有什麼用，不過你想去碰這個機關也沒那麼簡單，有個身材肥胖
的生物正擋在機關前面。
LONG);
    set("exits", ([
        "down" : __DIR__"right3.c",
    ]));
    set("detail", ([
        "機關": "似乎可以推動(push)的樣子。",
    ]));
    set("objects", ([
        __DIR__"npc/xiao.c" : 1,
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
        if( ob = present("_XIAO_", environment(me)) ) {
            message_vision(ob->query("name")+"說道："HIG"喳叭叭！不准碰機關！\n"NOR, me);
            message_vision(ob->query("name")+"說道："HIG"讓$N知道我「無聲之梟」的厲害！喳叭叭！\n"NOR, me);
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
