#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("鮑魚", ({ "abalone", "_ABALONE_" }));
    if( !clonep() ) {
        set("base_unit", "顆");
        set("base_value", 200);
        set("base_weight", 100);
        set("food_stuff", 10);              // 食物量，食品一定要有食物量
        set("long", "一顆帶著腥臭味的鮑魚。\n");
    }
    setup();
}
