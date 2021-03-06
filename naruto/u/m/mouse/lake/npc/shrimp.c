#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("蝦兵", ({ "shrimp soldier", "soldier" }) );
    set_race("beast");
    set_level(10);
    set("age", 5+random(105));
    set("long", "龍蝦小兵，時常在四周游來游去好像在巡邏。\n");
    set("limbs", ({ "蝦殼", "蝦鉗", "肚子", "蝦腳", "眼睛", "蝦尾" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance", 6);                 // 動作速率
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 3);          // 戰鬥速率
    set("chat_msg_combat", ({
        CYN"蝦兵不停的吐著泡泡。\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"food", "id":46, "amount":1, "p1":50, "p2":100 ]),  // 龍蝦沙拉
        ([ "type":"eq", "id":77, "amount":1, "p1":30, "p2":100 ]),    // 蝦殼
    }) );
    setup();
    // 增強
    set_temp("apply/armor", 150);            // 防禦力量
    set_stat_current("hp", 550);             // 體力
    set_stat_maximum("hp", 550);             // 最大值
}
