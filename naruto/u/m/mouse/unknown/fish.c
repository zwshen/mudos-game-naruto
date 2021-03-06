#include <npc.h>

void create()
{
    set_name("沼澤魚精", ({ "fish" }) );
    set_race("beast");
    set_level(30);

    set("long", "巨大的沼澤魚怪，強大的力量就算三個人也釣不起來。\n");

    set("limbs", ({ "魚頭", "魚身", "魚腹", "魚尾", "魚鰭" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 主動攻擊

    set("set_drop", ({
    //  ([ "type":"food", "id":??, "amount":1, "p1":40, "p2":100 ]),   // 魚心
    //  ([ "type":"food", "id":??, "amount":1, "p1":30, "p2":100 ]),   // 魚肺
    //  ([ "type":"food", "id":??, "amount":1, "p1":20, "p2":100 ]),   // 魚子
    //  ([ "type":"food", "id":??, "amount":1, "p1":10, "p2":100 ]),   // 魚精之鱗
    }) );
    setup();
}
