#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIR"¬õ¦â¾ð²G"NOR, ({ "red water", "water", "_HIR_WATER_" }));
    if( !clonep() ) {
        set("base_unit", "²~");
        set("unit", "²~");
        set("base_value", 20);
        set("base_weight", 10);
        set("long", "¤@²~¬õ¦âªº¾ð²G¡C");
    }
    setup();
}
