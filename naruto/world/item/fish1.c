#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("高路魚", ({ "gao lu fish", "fish", "_HOLENSO_B_" }));
    if( !clonep() ) {
        set("unit", "條");
        set("base_unit", "條");
        set("base_value", 20);
        set("base_weight", 100);
        set("food_stuff", 15);              // 食物量，食品一定要有食物量
        set("long", "一條長得奇形怪狀的魚。\n");
    }
    setup();
}
