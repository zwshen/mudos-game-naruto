#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("腐屍王", ({ "zombie king", "king" }) );
    set_race("beast");
    set_level(20);
    set("age", 450);
    set("nickname", "那傢伙");
    set("long", "肥肥胖胖的腐屍，看起來比其他腐屍還噁心。\n");
    set("limbs", ({ "屍首", "屍身", "屍足", "屍腿", "屍臂", "屍手", "屍肚" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance_combat", 5);          // 戰鬥動作
    set("chat_msg_combat", ({
        CYN"腐屍不停拖著身體移動，似乎想離開這裡。\n"NOR,
        CYN"腐屍的破肚中不停流出屍水。\n"NOR,
        CYN"腐屍發出「嗚∼∼哈∼∼」的怪聲。\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":100+random(300), "p1":80, "p2":100 ]), // 銀子
        ([ "type":"eq", "id":5, "amount":1+random(1), "p1":40, "p2":100 ]),       // 繩子
        ([ "type":"eq", "id":4, "amount":1, "p1":30, "p2":100 ]),                 // 皮帶
        ([ "type":"wp", "id":10, "amount":1, "p1":10, "p2":100 ]),                // 藤條
        ([ "type":"wp", "id":4, "amount":1, "p1":5, "p2":100 ]),                  // 殺豬刀
        ([ "type":"obj", "id":47, "amount":1, "p1":20, "p2":100 ]),               // 藍卷
    }) );
    setup();
    // 增強
    set_temp("apply/armor", 200);            // 防禦力量
    set_stat_current("hp", 1500);            // 體力
    set_stat_maximum("hp", 1500);            // 最大值
}
