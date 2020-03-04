#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIG"·ÏÂtºñ¨§"NOR, ({ "Smoke mung", "mung" }));
    if( !clonep() ) {
        set("base_unit", "ÁM");
        set("base_value", -1);
        set("unit", "ÁM");
        set("base_weight", 500);
        set("long", "ÄH³½®q¦Ñ±C±C¯Ó¶O¤ß¦å»s§@ªº¶Ç©_ºñ¨§¡C\n");
    }
    setup();
}
