#include <npc.h>

void create()
{
    set_name("±ï¬f³½", ({ "fish" }) );
    set_race("beast");
    set_level(8);
    set("long", "´Ï®§¦b¾ð®Úªþªñªº¯S¦³³½ºØ¡C\n");
    set("limbs", ({ "³½ÀY", "¨­Åé", "¸¡³¡", "³½§À", "³½Å_" }) );
    set("verbs", ({ "bite" }) );
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"food", "id":68, "amount":1, "p1":30, "p2":100 ]),   // ³½¦×
        ([ "type":"food", "id":69, "amount":1, "p1":80, "p2":100 ]),   // ³½¨{¦×
        ([ "type":"food", "id":70, "amount":1, "p1":30, "p2":100 ]),   // ³½­I¦×
        ([ "type":"food", "id":71, "amount":1, "p1":30, "p2":100 ]),   // ³½§À¦×
    }) );
    setup();
}
