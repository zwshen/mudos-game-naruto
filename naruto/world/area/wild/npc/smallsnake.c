#include <npc.h>

void create()
{
    set_name("¤p³D", ({ "small snake", "snake" }) );
    set_race("beast");
    set_level(5);

    set("long", "¤@°¦¥bªø¤£µuªº¤p³D¡C\n");

    set("limbs", ({ "³DÀY", "³D§À", "¸¡³¡" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // ¥D°Ê§ðÀ»

    set("set_drop", ({
        ([ "type":"food", "id":29, "amount":1, "p1":20, "p2":100 ]),   // ³D³J
        ([ "type":"food", "id":30, "amount":1, "p1":10, "p2":100 ]),   // ³DÁx
        ([ "type":"obj", "id":24, "amount":1, "p1":10, "p2":100 ]),   // ³D¥Ö
        ([ "type":"wp", "id":14, "amount":1, "p1":3, "p2":100 ]),   // ³D¤ú
    }) );

    setup();
}
