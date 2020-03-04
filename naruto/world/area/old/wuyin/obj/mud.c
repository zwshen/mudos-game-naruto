#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"Äêªd¤Ú"NOR, ({ "mud" }));
    if( !clonep() ) {
        set("base_unit", "ªb");
        set("base_value", 0);
        set("base_weight", 100);
        set("long", "¤@ªbÄêªd¤Ú¡C\n");
    }
    setup();
}
