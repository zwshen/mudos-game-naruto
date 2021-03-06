#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void do_fight()
{
    mapping cnd = ([]);

    if( this_object()->query_condition("snipe") != 0 ) return;

    message_vision(CYN"\n$N結印後雙手在眼睛附近一點，施展出了念技巧"HIW"「凝」\n"NOR, this_object());

    cnd["name"] = HIW"凝"NOR;
    cnd["duration"] = 300;
    cnd["exact"] = 50;
    cnd["defend"] = 0;

    this_object()->damage_stat("mp", 10, this_object());
    this_object()->set_condition("snipe", cnd);
    message_vision("$N成功將念集中在眼睛，提高部份命中力。\n\n"NOR, this_object());
    return;
}
void create()
{
    set_name("刀疤盜", ({ "scar bandit", "bandit" }));
    set_class("middle");
    set_level(29);
    set("camp", "hole_bandit");
    set("long", "臉上有塊刀疤的強盜，正很努力的修練念力的基礎「四大行」\n");
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":200+random(100), "p1":50, "p2":100 ]), // 銀子
        ([ "type":"obj", "id":22, "amount":1, "p1":5, "p2":100 ]),                // 黃金牙
        ([ "type":"wp", "id":16, "amount":1, "p1":1, "p2":1500 ]),                // 高原劍
        ([ "type":"eq", "id":66, "amount":1, "p1":1, "p2":100 ]),                 // 盜道鞋
        ([ "type":"eq", "id":67, "amount":1, "p1":1, "p2":150 ]),                 // 青銅護腕
    }) );
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();

    // 增強
    add_temp("apply/attack", 60);
    add_temp("apply/armor", 30);
    add_temp("apply/exact", 10);
    add_temp("apply/evade", 10);
    add_temp("apply/intimidate", 5);
    add_temp("apply/wittiness", 5);
    add_temp("apply/int", 5);
    add_temp("apply/con", 5);
    add_temp("apply/str", 5);
    add_temp("apply/dex", 5);
}
