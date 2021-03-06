#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("土著戰士", ({ "aborigines warrior", "warrior" }));
    set_race("human");
    set("gender", "male");
    set("age", 10+random(50));
    set_level(10);
    set("long", "土著的保衛戰士，手持刺槍驅逐外人進入。\n");
    set("attitude", "aggressive");
    set("set_drop", ({
        ([ "type":"food", "id":40, "amount":1+random(5), "p1":50, "p2":100 ]),  // 乾果
        ([ "type":"food", "id":38, "amount":1+random(2), "p1":30, "p2":100 ]),  // 樹果
        ([ "type":"food", "id":39, "amount":1+random(1), "p1":15, "p2":100 ]),  // 水果
        ([ "type":"food", "id":41, "amount":1, "p1":5, "p2":100 ]),             // 水果王
        ([ "type":"eq", "id":71, "amount":1, "p1":10, "p2":100 ]),              // 樹葉
        ([ "type":"wp", "id":20, "amount":1, "p1":1, "p2":200 ]),               // 刺槍
    }) );
    setup();
    // 增強
    set_temp("apply/attack", 240);          // 攻擊力量
    set_temp("apply/armor", 30);            // 防禦力量
    set_attr("str", 32);
    set_attr("dex", 31);
    set_temp("apply/exact", 50);            // 命中率
    set_temp("apply/armor", 31);            // 防禦力量
    set_temp("apply/intimidate", 10);       // 攻擊能力
    set_temp("apply/wittiness", 10);        // 防禦能力
    set_temp("apply/intimidate", 20);       // 攻擊能力
    set_skill("dodge", 50);              // 閃躲
    set_skill("savage hit", 50);         // 暴擊
    set_stat_current("hp", 750);         // 體力
    set_stat_maximum("hp", 750);         // 最大值

}

