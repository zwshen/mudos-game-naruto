inherit F_FOOD;

void create()
{
    set_name("大精力丸", ({ "big heal ap pill", "pill" }));
	if( !clonep() ) {
		set("unit", "堆");
		set("base_unit", "顆");
        set("base_value", 1000);
		set("base_weight", 10);
		set("food_stuff", 10);              // 食物量，食品一定要有食物量
        set("long", "一顆吃了可以立即恢復你的精神值100點。\n");
        set("heal_ap", 100);
	}
	setup();
}
