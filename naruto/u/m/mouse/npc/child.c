#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
    set_name("散財童子", ({ "Gold Child", "child" }));
    set("nickname",HIC"奉天散財"NOR);
    set("title",HIY"金山銀山"NOR);
    set_race("human");
    set_level(10+random(5));
    set("age", 10);
    set("long", "全身穿金帶銀的，一看就知道是有錢人家的小孩。\n");
    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":1000, "p1":100, "p2":100 ]),
    }) );
    set("chat_chance", 6);
    set("chat_msg", ({
        (: random_move :),
        CYN"散財童子身上金飾的反光刺到你的眼睛。\n"NOR,
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
       (: command, "help!" :),
       (: random_move :),
    }) );
    setup();
}
int accept_fight(object ob)
{
    do_chat(CYN"散財童子專心的數著鈔票，沒發現你的存在。"NOR"\n");
    return 0;
}
