#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("二人丹", ({ "twoman pill", "pill" }));
        set("unit", "顆");
        set("base_value", 3600);
        set("base_weight", 10);
        set("food_stuff", 1);   // 食物量，食品一定要有食物量
        set("long", "能補充精神與魔力的良藥。\n");
        set("heal", ([
            "ap": 900,
            "mp": 900,
        ]));
    setup();
}
