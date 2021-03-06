#include <ansi.h>
inherit F_FOOD;

void create()
{
        set_name("義大利麵", ({ "spaghetti" }));
        set("unit", "盤");
        set("base_value", 600);
        set("base_weight", 250);
        set("food_stuff", 50);              // 食物量，食品一定要有食物量
        set("long", "瓦傑所製作的義大利麵，根據瓦傑本人的說法，這些麵條是他將麵粉\n"
                    "吃進嘴後經過拌攪，然後用他特殊的網狀鼻毛將麵條擠出，再加上他\n"
                    "特製的義大利肉醬後完成！麵條香Ｑ有咬勁，還有種說不出的味道。\n"
                    "醬料風味獨特，搭配在一起真是好吃的不得了！不過這都是瓦傑自己\n"
                    "說的....到目前為止還沒人敢吃他做的義大利麵。\n"
                    "三十秒內恢復 600 點精力值、體力值、魔力值。\n" );
    set("condition", ([
            "food": ([
                "name": HIG"進食中"NOR,
                "heal_ap": 40,
                "heal_hp": 40,
                "heal_mp": 40,
                "duration": 15,
            ]),
        ]) );
        setup();
}
