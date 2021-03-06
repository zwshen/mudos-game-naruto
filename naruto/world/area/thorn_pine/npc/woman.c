#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void create()
{
    set_name("女豹人", ({ "bow woman", "woman" }));
    set_race("human");
    set_level(30);
    set("gender", "female");
    set("age", 10+random(81));
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "豹村的豹族人，正愉快的生活著。\n");
    set("camp", "bow");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
        (: command, "say 自從獵人考場在這之後，外來人愈來愈多了" :),
        CYN"女豹人擦著頭上的汗水。\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"wp", "id":33, "amount":1, "p1":20, "p2":100 ]),  // 木劍
        ([ "type":"wp", "id":34, "amount":1, "p1":10, "p2":100 ]),  // 刺木刀
        ([ "type":"wp", "id":43, "amount":1, "p1":5, "p2":100 ]),   // 斧頭
        ([ "type":"wp", "id":42, "amount":1, "p1":1, "p2":100 ]),   // 刺木槍
    }) );
    setup();
}
int accept_fight(object ob)
{
    if( this_player()->query_temp("quest/villpk") < 1) {
        do_chat(({
           (: command, "sorry" :),
           (: command, "say 族長有令，平時一律不準打架" :),
        }));
        return 0;
    }
    return ::accept_fight(ob);
}
