#include <npc.h>

void create()
{
    set_name("¨r³½", ({ "fish" }) );
    set_race("beast");
    set_level(10);
    set("long", "¥þ¨­¥ú¨r¨rªº³½Ãþ¡A³s³½Åì³£«D±`µ}¤Ö¡C\n");
    set("limbs", ({ "³½ÀY", "¨­Åé", "¸¡³¡", "³½§À", "³½Å_" }) );
    set("verbs", ({ "bite" }) );
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"food", "id":68, "amount":1, "p1":30, "p2":100 ]),   // ³½¦×
        ([ "type":"food", "id":69, "amount":1, "p1":30, "p2":100 ]),   // ³½¨{¦×
        ([ "type":"food", "id":70, "amount":1, "p1":80, "p2":100 ]),   // ³½­I¦×
        ([ "type":"food", "id":71, "amount":1, "p1":30, "p2":100 ]),   // ³½§À¦×
        ([ "type":"food", "id":73, "amount":1, "p1":5, "p2":100 ]),    // ³½¨xªo
    }) );
    setup();
}
