// write by -Mouse-

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("瘋狗", ({ "dog" }));
    set_race("beast");
    set_level(5);
    set("age", 6+random(10));
    set("long", "得了狂犬病的野狗，嘴角不停流著口水。\n");
    set("limbs", ({ "狗頭", "身體", "腹部", "狗腿", "尾巴" }) ); //攻擊部位
    set("verbs", ({ "bite" }) );                                 //攻擊方式
    // 設定掉落物結構： (分子/分母) 是掉落機率
    // ({ ([ "type":類別, "id":編號, "amount":數量, "p1":分子, "p2":分母 ]),
    //    ([ ... ]), ([ ... ]), ... })
    set("set_drop", ({
        ([ "type":"eq", "id":5, "amount":1, "p1":20, "p2":100 ]),     // 繩子
    }) );
    set("attitude", "aggressive");         // 主動攻擊
    setup();

    // 削弱
    set_attr("str", 15);
    set_attr("con", 10);
    set_attr("dex", 10);
    set_attr("int", 10);
    set_temp("apply/attack", -5);         // 攻擊力量
    set_temp("apply/defend", -5);         // 防禦力量
    set_temp("apply/exact", -5);          // 命中率
    set_temp("apply/evade", -5);          // 迴避率
    set_temp("apply/intimidate", -5);     // 攻擊能力
    set_temp("apply/wittiness", -5);      // 防禦能力
}
