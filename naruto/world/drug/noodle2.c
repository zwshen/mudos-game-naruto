#include <ansi.h>
inherit F_FOOD;

void create()
{
	set_name("正油拉麵", ({ "noodles" }));
	set("unit", "碗");
	set("base_value", 900);
	set("base_weight", 300);
	set("food_stuff", 50);              // 食物量，食品一定要有食物量
	set("long", "這是一碗一樂拉麵館老闆所做的正油拉麵，湯頭是以雞骨為主原料，\n"
                "配以昆布去除肉腥味，再加上柴魚、小魚干、醬油一起熬製，並放上\n"
                "塊狀海苔，湯汁清澈，味道清淡再加上爽口、味美的叉燒、筍乾、魚\n"
                "板、銀牙、玉子、豆苗，看了就讓人忍不住流口水。\n"
                "三十秒內恢復 900 點精力值、體力值、魔力值。\n" );
	set("condition", ([
	    "food": ([
	        "name": HIG"進食中"NOR,
	        "heal_ap": 60,
	        "heal_hp": 60,
	        "heal_mp": 60,
	        "duration": 15,
	    ]),
	]) );
	setup();
}
