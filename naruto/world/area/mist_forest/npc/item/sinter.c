#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(RED"燒土"NOR, ({ "sinter" }));
    if( !clonep() ) {
        set("base_unit", "團");
        set("unit", "團");
        set("base_value", 5);
        set("base_weight", 1);
        set("long", "因為地形影響燒結的土壤，雖然很硬但是卻難以結塊。");
    }
    setup();
}