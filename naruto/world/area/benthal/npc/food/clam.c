#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("蚌殼", ({ "clam" }));
    if( !clonep() ) {
        set("unit", "顆");
        set("base_unit", "顆");
        set("base_value", 20);
        set("base_weight", 100);
        set("food_stuff", 15);              // 食物量，食品一定要有食物量
        set("long", "隨處可見的海中有殼生物。\n");
    }
    setup();
}
