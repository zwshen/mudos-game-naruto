#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("蟹將", ({ "crab general", "general" }) );
    set_race("beast");
    set_level(12);
    set("age", 5+random(105));
    set("long", "螃蟹大將，不時的展現牠的巨鉗向你示威。\n");
    set("limbs", ({ "蟹殼", "蟹鉗", "肚子", "蟹腳", "眼睛", "巨鉗" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance", 6);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 3);
    set("chat_msg_combat", ({
        CYN"蟹將揮舞著巨鉗向你示威。\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"food", "id":44, "amount":1, "p1":50, "p2":100 ]),  // 蟹肉白盅
        ([ "type":"eq", "id":75, "amount":1, "p1":30, "p2":100 ]),    // 蟹殼
        ([ "type":"wp", "id":23, "amount":1, "p1":10, "p2":100 ]),    // 蟹鉗
    }) );
    setup();

    // 增強
    add_temp("apply/armor", 50);
}
