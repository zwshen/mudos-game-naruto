#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIG"³D¬r"NOR, ({ "snake venom", "venom" }));
    if( !clonep() ) {
        set("base_unit", "²~");
        set("unit", "²~");
        set("base_value", 500);
        set("base_weight", 100);
        set("long", "¤@²~³Dªº¬r²G¡C\n");
    }
    setup();
}
