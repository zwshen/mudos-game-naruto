#include <ansi.h>
inherit F_FOOD;
void create()
{
    set_name(HIR"魚子"NOR, ({ "fish's child", "child" }));
    if( !clonep() ) {
        set("base_unit", "團");
        set("unit", "團");
        set("base_value", 30);
        set("base_weight", 100);
        set("food_stuff", 5);
        set("long", "又稱魚卵，是魚種味道最佳的部份。\n");
    }
    setup();
}
