#include <ansi.h>
inherit F_FOOD;

void create()
{
    set_name("酸辣麵", ({ "noodles" }));
    set("unit", "碗");
    set("base_value", 2000);
    set("base_weight", 100);
    set("food_stuff", 80);              // 食物量，食品一定要有食物量
    set("long", "老張除了牛肉麵的另一手絕活，無人能夠抵擋的「酸辣麵」酸中帶辣\n"
                "，口感灼熱有勁，首先將麵條吸入口中，一陣酸甘又不麻舌的口感瞬\n"
                "間充滿口中，咀嚼麵條時麵條所吸附的濃辣麵湯開始發威，一陣陣辣\n"
                "感讓人直衝腦門，精神整個都好起來了，心情也為之一振。在吃完麵\n"
                "後將湯一起下肚，不但能去除剛才麵中的油膩，淡淡的辣味也能將口\n"
                "中的酸辣去除，實在是碗不可多得的好麵。\n"
                "三十秒內恢復 1500 點精力值、體力值、魔力值。\n" );
    set("condition", ([
        "food": ([
            "name": HIG"進食中"NOR,
            "heal_ap": 100,
            "heal_hp": 100,
            "heal_mp": 100,
            "duration": 15,
        ]),
    ]) );
    setup();
}
