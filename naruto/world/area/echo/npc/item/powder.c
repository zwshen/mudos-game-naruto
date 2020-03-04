#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("牙粉", ({ "tooth powder", "powder" }));
        set("unit", "包");
        set("base_value", 100);            // 初期的藥，不需要太貴，讓玩家買得起
        set("base_weight", 100);
        set("food_stuff", 5);              // 食物量，食品一定要有食物量
        set("long", "山狼虎牙所磨成的粉，能夠快速回復ＭＰ。\n"
                    "三十秒內恢復 300 點魔力值。\n" );
set("condition", ([
    "food": ([
        "name": HIG"進食中"NOR,
        "heal_mp": 20,
        "duration": 15,
    ]),
]) );
    setup();
}

