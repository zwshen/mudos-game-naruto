#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name(RED"鼠目"NOR, ({ "mouse's eyes", "eyes" }));
    if( !clonep() ) {
        set("base_unit", "對");
        set("base_value", 10);
        set("base_weight", 100);
        set("food_stuff", 8);              // 食物量，食品一定要有食物量
        set("long", "一對血淋淋的老鼠眼睛。\n");
    }
    setup();
}
