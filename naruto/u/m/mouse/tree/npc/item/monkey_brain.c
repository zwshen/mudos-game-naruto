#include <ansi.h>

inherit F_FOOD;

void create()
{
    set_name(HIR"猴腦"NOR, ({ "monkey brain", "brain", "_MONKEY_BRAIN_" }));
    if( !clonep() ) {
        set("base_unit", "顆");
        set("base_value", 100);
        set("base_weight", 500);
        set("food_stuff", 20);
        set("long", "猴子的腦，是一種非常奢侈的食材。\n");
    }
    setup();
}
