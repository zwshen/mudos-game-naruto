#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("牛肉", ({ "beef", "_CHILI_E_" }));
    if( !clonep() ) {
        set("unit", "塊");
        set("base_unit", "塊");
        set("base_value", 10);
        set("base_weight", 10);
        set("food_stuff", 10);
        set("long", "好吃的牛肉，保證來源是沒有狂牛症的牛隻。\n");
    }
    setup();
}
