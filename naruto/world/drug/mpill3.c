#include <ansi.h>
inherit F_FOOD;

void create()
{
	set_name("大菊花茶", ({ "big daisy tea", "tea" }));
	set("unit", "杯");
	set("base_value", 200);            // 初期的藥，不需要太貴，讓玩家買得起
	set("base_weight", 100);
	set("food_stuff", 30);             // 食物量，食品一定要有食物量
	set("long",
	    "一杯菊花茶，在進食的過程中，可以恢復你的魔力值(MP)。\n"
	    "三十秒內恢復 600 點魔力值。\n"
	);
	set("condition", ([
	    "food": ([
	        "name": HIG"進食中"NOR,
	        "heal_mp": 40, 
	        "duration": 15,
	    ]),
	]) );
	setup();
}
