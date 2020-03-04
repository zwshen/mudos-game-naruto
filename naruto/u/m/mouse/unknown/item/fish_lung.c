#include <ansi.h>
inherit F_FOOD;
void create()
{
    set_name(RED"³½ªÍ"NOR, ({ "fish's lung", "lung" }));
    if( !clonep() ) {
        set("base_unit", "Áû");
        set("unit", "Áû");
        set("base_value", 20);
        set("base_weight", 100);
        set("food_stuff", 5);
        set("long", "¤@Áû¸{¯äªº³½ªÍ¡C\n");
    }
    setup();
}
