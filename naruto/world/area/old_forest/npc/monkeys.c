#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("巨猴", ({ "big monkey", "monkey" }));
    set_race("beast");
    set_level(15);
    set("age", 20+random(60));
    set("long", "比一般猴子還高兩個頭的巨大猴子。\n");
    set("limbs", ({ "猴頭", "身體", "肚子", "猴臂", "尾巴", "猴背", "屁股" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("set_drop", ({
        ([ "type":"obj", "id":37, "amount":1+random(2), "p1":100, "p2":100 ]),  // 猴屎
        ([ "type":"obj", "id":38, "amount":1+random(11), "p1":80, "p2":100 ]),  // 猴牙
        ([ "type":"eq", "id":73, "amount":1, "p1":60, "p2":100 ]),              // 猴皮
        ([ "type":"food", "id":43, "amount":1+random(1), "p1":50, "p2":100 ]),  // 猴掌
        ([ "type":"food", "id":42, "amount":1, "p1":20, "p2":100 ]),            // 猴腦
        ([ "type":"eq", "id":72, "amount":1, "p1":5, "p2":100 ]),               // 猴臂
    }) );
    setup();

    // 加強
    add_temp("apply", (["armor":10, "attack":20, "intimidate":20 ]) );
}
