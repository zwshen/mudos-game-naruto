#include <npc.h>

void create()
{
    set_name("大置弱魚", ({ "fish" }) );
    set_race("beast");
    set_level(12);
    set("long", "體型龐大但是卻十分弱懦的魚，遇到大魚只會裝死。\n");
    set("limbs", ({ "魚頭", "身體", "腹部", "魚尾", "魚鰭" }) );
    set("verbs", ({ "bite" }) );
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"food", "id":68, "amount":1, "p1":30, "p2":100 ]),   // 魚肉
        ([ "type":"food", "id":69, "amount":1, "p1":30, "p2":100 ]),   // 魚肚肉
        ([ "type":"food", "id":70, "amount":1, "p1":30, "p2":100 ]),   // 魚背肉
        ([ "type":"food", "id":71, "amount":1, "p1":80, "p2":100 ]),   // 魚尾肉
        ([ "type":"food", "id":73, "amount":1, "p1":10, "p2":100 ]),   // 魚肝油
    }) );
    setup();
}
