#include <ansi.h>
#include <npc.h>

inherit F_SEABANDIT;

void create()
{
    set_name("品客", ({ "pin ke", "pin", "ke" }) );
    set_race("human");
    set_level(30);
    set("title",HIR"三日月"NOR);
    set("nickname", "翹鬍子船長");
    set("gender", "male");
    set("class","thief_sea");
    set("camp", "robber");
    set("age", 45);
    set("long", "臉上掛著彎月型的鬍鬚，一臉賊樣似乎是三日月海賊團的船長。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        (: command, "say 聽說死亡碉堡內有神秘的財寶！我正在想辦法進去！" :),
        (: command, "angry" :),
    }));
    set("set_drop", ({
        ([ "type":"wp", "id":2, "amount":1, "p1":25, "p2":100 ]),         // 大刀
        ([ "type":"wp", "id":12, "amount":1, "p1":1, "p2":100 ]),         // 砍馬大刀
        ([ "type":"wp", "id":69, "amount":1, "p1":10, "p2":100 ]),        // 長刀
    }) );
    setup();
    carry_object("/world/area/wild/npc/wp/blade.c")->wield();
}
void relay_say(object ob, string arg)
{
    if( arg == "死亡碉堡" )  {
        do_chat(({
            (: command, "hehe" :),
            (: command, "say 那碉堡上有座天枰知道嗎？！" :),
            (: command, "say 大家都能猜到只要重量放對就會有機關吧！" :),
            (: command, "say 不過那上面的風太強了！根本沒東西可以放！" :),
            (: command, "say 最近卻讓我找到一樣東西一定可以！" :),
            (: command, "say 想知道嗎？才不告訴你！" :),
        }));
        return;
    }
    if( arg == "財寶" )  {
        do_chat(({
            (: command, "think" :),
            (: command, "say 聽說是什麼魂還是啥的..反正應該很值錢！" :),
            (: command, "say 不然也不會一堆人搶著要！" :),
        }));
        return;
    }
}
