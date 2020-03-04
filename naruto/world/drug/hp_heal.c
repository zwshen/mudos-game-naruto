inherit F_FOOD;

void create()
{
    set_name("體力丸", ({ "heal hp pill", "pill" }));
    set("unit", "顆");
    set("base_value", 600);
    set("base_weight", 10);
    set("food_stuff", 1);              // 食物量，食品一定要有食物量
    set("long", "吃了可以立即恢復你的體力值(HP) 300 點。\n");
    set("heal", ([
        "hp": 300,
    ]) );
	setup();
}
