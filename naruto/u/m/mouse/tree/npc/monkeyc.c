#include <npc.h>

void create()
{
    set_name("小猴", ({ "child monkey", "monkey" }) );
    set_race("beast");
    set_level(5);
    set("age", 1+random(12));
    set("long", "活蹦亂跳的小猴子。\n");

    set("limbs", ({ "猴頭", "身體", "肚子", "猴臂", "尾巴", "猴背", "屁股" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("set_drop", ({
        ([ "type":"obj", "id":37, "amount":1+random(4), "p1":80, "p2":100 ]),   // 猴屎
        ([ "type":"obj", "id":38, "amount":1+random(2), "p1":50, "p2":100 ]),   // 猴牙
        ([ "type":"eq", "id":73, "amount":1, "p1":30, "p2":100 ]),              // 猴皮
    }) );
    setup();
    // 削弱
    set_temp("apply/attack", -10);         // 攻擊力量
    set_temp("apply/defend", -10);         // 防禦力量
    set_temp("apply/exact", -10);          // 命中率
    set_temp("apply/evade", -10);          // 迴避率
    set_temp("apply/intimidate", -10);     // 攻擊能力
    set_temp("apply/wittiness", -10);      // 防禦能力
}

