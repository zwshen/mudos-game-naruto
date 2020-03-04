#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIG"ºñ¦â¾ð²G"NOR, ({ "green water", "water", "_HIG_WATER_" }));
    if( !clonep() ) {
        set("base_unit", "²~");
        set("unit", "²~");
        set("base_value", 1);
        set("base_weight", 10);
        set("no_box", 1);
        set("long", "¤@²~ºñ¦âªº¾ð²G¡C");
    }
    setup();
}
