#include <ansi.h>
inherit F_FOOD;

void create()
{
        set_name("蟹黃燒賣", ({ "meat roe dumpling","dumpling" }));
                set("unit", "份");
                set("base_value", 150);
                set("base_weight", 200);
                set("food_stuff", 20);              // 食物量，食品一定要有食物量
                set("long", "這是一份新鮮蟹黃做成的燒賣，十分美味可口。\n"
                    "三十秒內恢復 150 點精力值、體力值、魔力值。\n" );
set("condition", ([
    "food": ([
        "name": HIG"進食中"NOR,
        "heal_ap": 10,
        "heal_hp": 10,
        "heal_mp": 10,
        "duration": 15,
    ]),
]) );
        setup();
}
