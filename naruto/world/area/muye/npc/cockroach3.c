#include <npc.h>

void create()
{
    set_name("¥¨Á­½¸", ({ "large cockroach", "cockroach" }) );
    set_race("beast");
    set_level(5);

    set("long", "¤@°¦äú¤ßªº¤jÁ­½¸¡C\n");

    set("limbs", ({ "Á­ÀY", "¨­Åé", "¸¡³¡", "Á­»L", "§À¤Ú" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // ¥D°Ê§ðÀ»

    set("set_drop", ({
        ([ "type":"obj", "id":25, "amount":1, "p1":80, "p2":100 ]),   // Á­½¸Ä²¨¤
        ([ "type":"food", "id":34, "amount":1, "p1":60, "p2":100 ]),   // Á­½¸§Z
        ([ "type":"obj", "id":26, "amount":1, "p1":80, "p2":100 ]),   // Á­½¸¸}
    }) );

    setup();
}