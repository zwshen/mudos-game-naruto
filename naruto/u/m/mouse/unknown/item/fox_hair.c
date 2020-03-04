#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"ª°¤ò"NOR, ({ "fox hair", "hair", "_FOX_HAIR_" }) );

    if( !clonep() ) {
        set("base_unit", "®Ú");
        set("unit", "®Ú");
        set("base_value", 30);
        set("base_weight", 400);
        set("long", "¤@®Ú´Ä¦âªºª°ºµ¤ò¡C\n");
    }
    setup();
}
