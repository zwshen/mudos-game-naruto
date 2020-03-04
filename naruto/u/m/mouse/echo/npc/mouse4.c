#include <npc.h>

void create()
{
    set_name("跑公", ({ "mutation earth mouse", "mouse" }) );
    set_race("beast");
    set_level(8);
    set("long", "唉璂璂φΨ疭跑公\n");
    set("limbs", ({ "公繷", "ō砰", "浮场", "公籐", "Юぺ" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 笆ю阑
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"food", "id":35, "amount":1, "p1":80, "p2":100 ]),   // 公ヘ
        ([ "type":"food", "id":36, "amount":1, "p1":80, "p2":100 ]),   // 公竲
        ([ "type":"food", "id":37, "amount":1, "p1":80, "p2":100 ]),   // 公Ю
        ([ "type":"food", "id":56, "amount":1, "p1":15, "p2":100 ]),   // 公福
    }) );
    setup();
}
