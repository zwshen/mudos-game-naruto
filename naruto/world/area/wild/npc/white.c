#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("白盜", ({ "white bandit", "bandit" }));
    set_class("middle");
    set_level(33);
    set("nickname", HIW"黑白兩道"NOR);
    set("long", "身穿世界政府官員的正式服裝，不過他在這裡並不是在捉拿強盜，而\n"
                "是不斷的跟強盜們交頭接耳，好像正在討論什麼奸詐的計劃。\n");
    set("camp", "hole_bandit");
    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":1, "p1":10, "p2":100 ]),       // 黃金
        ([ "type":"wp", "id":16, "amount":1, "p1":1, "p2":700 ]),         // 高原劍
        ([ "type":"wp", "id":70, "amount":1, "p1":1, "p2":1500 ]),        // 山峰劍
        ([ "type":"eq", "id":66, "amount":1, "p1":5, "p2":100 ]),         // 盜道鞋
        ([ "type":"eq", "id":67, "amount":1, "p1":1, "p2":100 ]),         // 青銅護腕
    }) );
    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    setup();
    carry_object(_DIR_AREA_"wild/npc/wp/gao_sword.c")->wield("righthand");

    // 增強
    add_temp("apply/attack", 100);
    add_temp("apply/armor", 60);
    add_temp("apply/exact", 20);
    add_temp("apply/evade", 20);
    add_temp("apply/intimidate", 10);
    add_temp("apply/wittiness", 10);
    add_temp("apply/int", 7);
    add_temp("apply/con", 7);
    add_temp("apply/str", 7);
    add_temp("apply/dex", 7);
}
