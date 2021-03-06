#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("腐屍", ({ "zombie" }) );
    set_race("beast");
    set_level(16);
    set("age", 580);
    set("nickname", "林北");
    set("long", "總管林北的腐屍，還是跟其他腐屍一樣噁心。\n");
    set("limbs", ({ "屍首", "屍身", "屍足", "屍腿", "屍臂", "屍手" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance_combat", 5);          // 戰鬥動作
    set("chat_msg_combat", ({
        NOR"腐屍怨聲載道﹕"HIG"我恨阿∼我的寶物∼∼恨阿∼\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":100+random(150), "p1":70, "p2":100 ]), // 銀子
        ([ "type":"eq", "id":5, "amount":1+random(1), "p1":40, "p2":100 ]),       // 繩子
        ([ "type":"eq", "id":4, "amount":1, "p1":30, "p2":100 ]),                 // 皮帶
        ([ "type":"obj", "id":42, "amount":1, "p1":40, "p2":100 ]),               // 機關紙
        ([ "type":"wp", "id":3, "amount":1, "p1":5, "p2":100 ]),                  // 單刀
    }) );
    setup();
    // 增強
    set_temp("apply/attack", 30);            // 攻擊力量
    set_temp("apply/armor", 200);            // 防禦力量
    set_stat_current("hp", 1000);            // 體力
    set_stat_maximum("hp", 1000);            // 最大值
}
