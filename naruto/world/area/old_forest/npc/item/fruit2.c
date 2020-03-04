#include <ansi.h>

inherit F_FOOD;

void create()
{
    set_name(MAG"水果"NOR, ({ "Fruit", "fruit", "_WATER_FRUIT_" }));
    if( !clonep() ) {
        set("base_unit", "顆");
        set("base_value", 20);
        set("base_weight", 200);
        set("food_stuff", 5);
        set("long", "樹上成熟的水果。\n");
    }
    setup();
}
