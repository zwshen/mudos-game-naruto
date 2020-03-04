#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name(HIR"¬õÅÚ½³"NOR, ({ "beet", "_KARE_A_" }));
    if( !clonep() ) {
        set("unit", "®Ú");
        set("base_unit", "®Ú");
        set("base_value", 15);
        set("base_weight", 10);
        set("food_stuff", 20);
        set("no_sell", 1);
        set("long", "¬õ¦â½­µæ¡A§t¦³Â×´I­JÅÚ½³¯À¡C\n");
    }
    setup();
}
