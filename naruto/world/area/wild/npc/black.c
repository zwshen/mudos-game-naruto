#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("黑盜", ({ "black bandit", "bandit" }));
    set_class("middle");
    set_level(33);
    set("nickname", HIK"黑白兩道"NOR);
    set("long", "被黑道所派遣而來的人員，因為黑道們想徵召一批類似流星街的無名\n"
                "殺手，這裡的流浪忍者正好是最佳目標，因此立刻派手下來這接洽。\n");
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
