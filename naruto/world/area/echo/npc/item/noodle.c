#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("牛肉麵", ({ "noodles", "_BEEF_NOODLES_" }));
        set("unit", "碗");
        set("base_unit", "碗");
        set("base_value", 300);
        set("base_weight", 200);
        set("food_stuff", 50);
        set("no_box", 1);
        set("long", @LONG
由賣麵的老張所做的上等牛肉麵，所用的原料是上等牛肉，大骨頭和
多種蔬菜所熬成的美味湯頭，麵條香Ｑ有勁，搭配有少許牛筋的爽口
牛肉，吃完之後再一喝湯，馬上將剛才所嘗的美味又一次的灌入口中
，讓人回味無窮，讚不絕口。
三十秒內恢復 300 點精力值、體力值、魔力值。
LONG);
set("condition", ([
    "food": ([
        "name": HIG"進食中"NOR,
        "heal_ap": 20,
        "heal_hp": 20,
        "heal_mp": 20,
        "duration": 15,
    ]),
]) );

    setup();
}
