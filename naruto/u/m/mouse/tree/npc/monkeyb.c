#include <npc.h>

void create()
{
    set_name("公猴", ({ "male monkey", "monkey" }));
    set_race("beast");
    set_level(15);
    set("age", 16+random(40));
    set("long", "身材壯碩的大猴子，時常吱吱叫個不停。\n");
    set("limbs", ({ "猴頭", "身體", "肚子", "猴臂", "尾巴", "猴背", "屁股" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("set_drop", ({
        ([ "type":"obj", "id":37, "amount":1+random(9), "p1":50, "p2":100 ]),   // 猴屎
        ([ "type":"obj", "id":38, "amount":1+random(5), "p1":70, "p2":100 ]),   // 猴牙
        ([ "type":"eq", "id":73, "amount":1, "p1":50, "p2":100 ]),              // 猴皮
        ([ "type":"food", "id":43, "amount":1+random(1), "p1":50, "p2":100 ]),  // 猴掌
        ([ "type":"food", "id":42, "amount":1, "p1":10, "p2":100 ]),            // 猴腦
        ([ "type":"obj", "id":36, "amount":1, "p1":5, "p2":100 ]),              // 古老地圖
    }) );
    setup();
    // 削弱
    set_temp("apply/exact", -5);          // 命中率
    set_temp("apply/evade", -5);          // 迴避率
}

