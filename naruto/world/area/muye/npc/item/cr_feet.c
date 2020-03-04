#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"Á­½¸¸}"NOR, ({ "cockroach's foot", "foot" }));
    if( !clonep() ) {
        set("base_unit", "¤ä");
        set("base_value", 4);
        set("base_weight", 100);
        set("long", "¤@¤ä´c¯äªºÁ­½¸¸}¡C\n");
    }
    setup();
}