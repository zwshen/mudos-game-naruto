#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("腦漿膏", ({ "brains fat", "fat" }));
        set("unit", "塊");
        set("base_value", 100);
        set("base_weight", 100);
        set("food_stuff", 5);              // 食物量，食品一定要有食物量
        set("long", "一塊用鼠腦漿製成的膏，能夠加快精神回復。\n"
                    "三十秒內恢復 300 點精力值。\n" );
set("condition", ([
    "food": ([
        "name": HIG"進食中"NOR,
        "heal_ap": 20,
        "duration": 15,
    ]),
]) );
    setup();
}
