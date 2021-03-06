#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("釣客", ({ "fishing man", "man" }));
    set_race("human");
    set_level(20);
    set("age", 25+random(10));

    set("long", "一個好整以暇拿著釣竿在釣著魚的釣客。\n");

    set("chat_chance", 1);
    set("chat_msg", ({
        "釣客喘了幾口氣道：怎麼盡釣些奇怪東西...\n",
        (: command,"sweat":),
    }));

    // 設定掉落物結構： (分子/分母) 是掉落機率
    // ({ ([ "type":類別, "id":編號, "amount":數量, "p1":分子, "p2":分母 ]),
    //    ([ ... ]), ([ ... ]), ... })
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":20+random(10), "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"eq", "id":21, "amount":1, "p1":20, "p2":100 ]),     // 布手套
        ([ "type":"eq", "id":7, "amount":1, "p1":20, "p2":100 ]),     // 布衣
        ([ "type":"eq", "id":64, "amount":1, "p1":5, "p2":100 ]),     // 斗笠
        ([ "type":"wp", "id":15, "amount":1, "p1":20, "p2":100 ]),     // 釣竿
    }) );

    setup();
}
