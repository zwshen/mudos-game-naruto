//traveller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("過路客", ({ "traveller" }) );
    set("unit", "位");
    set("gender", "male");
    set_level(6);
    set("age", 18+random(60));
    set("long", "一位行色匆匆，滿臉風霜的過路客，一身勁裝，似乎隨時又要上路去。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "過路客喘了幾口氣道：呼 呼... 好累，真遠。\n",
        "過路客似乎累的講不出話來了。\n",
        (: command,"sweat":),
        (: random_move :),
    }));

    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":21+random(10), "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"obj", "id":30, "amount":1, "p1":3, "p2":100 ]),  // 麻布袋
        ([ "type":"eq", "id":7, "amount":1, "p1":10, "p2":100 ]),     // 布衣
        ([ "type":"wp", "id":10, "amount":1, "p1":10, "p2":100 ]),    // 短劍
    }) );

    setup();
}

int accept_fight(object ob)
{
    do_chat("過路客擦了擦脖子上的汗水笑道：「打啥，都快累翻了還打！」\n");
    return 0;
}
