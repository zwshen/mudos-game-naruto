#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("鯊魚肉", ({ "shark's meat", "meat" }));
    if( !clonep() ) {
        set("unit", "塊");
        set("base_unit", "塊");
        set("base_value", 10);
        set("base_weight", 100);
        set("food_stuff", 10);              // 食物量，食品一定要有食物量
        set("long", "鯊魚肉肉質較硬，似乎不太適合食用。\n");
    }
    setup();
}
