// write by -Acme-

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("乞丐", ({ "beggar" }));
    set_race("human");
    set_level(5);
    set("title", "丐幫");
    set("nickname", "叫化子");
    set("age", random(50)+10);
    set("long", "一位穿著破破爛爛乞丐，蓬頭垢面不時的散發臭味，令人作噁。\n");
    // 隨機移動
    set("chat_chance", 1);
    set("chat_msg", ({
        (: random_move :),
    }));

    // 設定掉落物結構： (分子/分母) 是掉落機率
    // ({ ([ "type":類別, "id":編號, "amount":數量, "p1":分子, "p2":分母 ]),
    //    ([ ... ]), ([ ... ]), ... })
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":random(10)+1, "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"eq", "id":7, "amount":1, "p1":10, "p2":100 ]),     // 布衣
    }) );

    setup();

    // 削弱
    set_attr("str", 15);
    set_attr("con", 15);
    set_attr("dex", 15);
    set_attr("int", 15);
    set_temp("apply/attack", -3);         // 攻擊力量
    set_temp("apply/defend", -3);         // 防禦力量
    set_temp("apply/exact", -3);          // 命中率
    set_temp("apply/evade", -3);          // 迴避率
    set_temp("apply/intimidate", -3);     // 攻擊能力
    set_temp("apply/wittiness", -3);      // 防禦能力
}
