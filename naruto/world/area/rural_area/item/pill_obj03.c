#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name(HIG"芹菜"NOR, ({ "celery", "_CHILI_A_" }));
    if( !clonep() ) {
        set("unit", "根");
        set("base_unit", "根");
        set("base_value", 10);
        set("base_weight", 10);
        set("food_stuff", 10);
        set("no_sell", 1);
        set("long", "綠色的青菜，聞起來有種特別的味道。\n");
    }
    setup();
}
