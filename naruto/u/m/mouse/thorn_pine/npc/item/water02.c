#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIM"µµ¦â¾ð²G"NOR, ({ "purple water", "water", "_HIM_WATER_" }));
    if( !clonep() ) {
        set("base_unit", "²~");
        set("unit", "²~");
        set("base_value", 20);
        set("base_weight", 10);
        set("long", "¤@²~µµ¦âªº¾ð²G¡C");
    }
    setup();
}
