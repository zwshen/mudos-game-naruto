#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name(HIG"菠菜"NOR, ({ "spinage", "_HOLENSO_A_" }));
    if( !clonep() ) {
        set("unit", "棵");
        set("base_unit", "棵");
        set("base_value", 10);
        set("base_weight", 10);
        set("food_stuff", 10);
        set("no_sell", 1);
        set("long", "綠色的青菜，吃了對身體有幫助。\n");
    }
    setup();
}
