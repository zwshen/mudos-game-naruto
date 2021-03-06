#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("居民", ({ "inhabitant" }) );
    set_race("human");
    set_level(5);
    set("long", "鯨魚島的住民，生活安逸，臉上總是面帶笑容。\n");
    set("age", 5+random(80));
    set("chat_chance", 6);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":16+random(10), "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"eq", "id":7, "amount":1, "p1":10, "p2":100 ]),     // 布衣
        ([ "type":"wp", "id":10, "amount":1, "p1":10, "p2":100 ]),    // 藤條
    }) );
    setup();
}
