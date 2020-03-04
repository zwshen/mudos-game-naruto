#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("海膽", ({ "urchin" }));
    if( !clonep() ) {
        set("unit", "粒");
        set("base_unit", "粒");
        set("base_value", 20);
        set("base_weight", 100);
        set("food_stuff", 15);              // 食物量，食品一定要有食物量
        set("long", "外皮有刺的海洋生物，裡面肉質滑嫩鮮美。\n");
    }
    setup();
}
