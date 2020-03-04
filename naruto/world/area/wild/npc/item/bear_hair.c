#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"ºµ¤ò"NOR, ({ "bear's hair", "hair" }));

    if( !clonep() ) {
        set("base_unit", "®Ú");
        set("base_value", 50);
        set("base_weight", 600);
        set("long", "¤@®Ú²Ê²Ê¦Ç¦Çªººµ¤ò¡C\n");
    }
    setup();
}
