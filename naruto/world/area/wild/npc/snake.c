#include <npc.h>

void create()
{
    set_name("³D", ({ "snake" }) );
    set_race("beast");
    set_level(8);

    set("long", "¤@°¦²ÊªÎªº³D¡C¡C\n");

    set("limbs", ({ "³DÀY", "³D§À", "¸¡³¡" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // ¥D°Ê§ðÀ»

    set("set_drop", ({
        ([ "type":"food", "id":29, "amount":1, "p1":25, "p2":100 ]),   // ³D³J
        ([ "type":"food", "id":30, "amount":1, "p1":15, "p2":100 ]),   // ³DÁx
        ([ "type":"obj", "id":24, "amount":1, "p1":15, "p2":100 ]),   // ³D¥Ö
        ([ "type":"wp", "id":14, "amount":1, "p1":7, "p2":100 ]),   // ³D¤ú
        ([ "type":"obj", "id":108, "amount":1, "p1":1, "p2":500 ]),   // ­¸¤Ñ·ÆªO
    }) );

    setup();
}
