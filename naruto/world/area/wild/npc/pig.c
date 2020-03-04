#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(HIK"¶Â½Þ"NOR, ({ "black pig", "pig" }) );
    set_race("beast");
    set_level(7);

    set("long", "¤@°¦ªÎ´þ´þªº¶Â½Þ¡A¤@°Æ¥û¬½ªº¼Ë¤l¡C\n");

    set("limbs", ({ "½ÞÀY", "¨­Åé", "¸¡³¡", "½Þ»L", "§À¤Ú" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // ¥D°Ê§ðÀ»

    set("set_drop", ({
        ([ "type":"food", "id":31, "amount":1, "p1":80, "p2":100 ]),   // ½Þ¸z
        ([ "type":"eq", "id":55, "amount":1, "p1":50, "p2":100 ]),   // ¶Â½Þ¥Ö
        ([ "type":"eq", "id":56, "amount":1, "p1":40, "p2":100 ]),   // ¶Â½ÞÀY
    }) );

    setup();
}