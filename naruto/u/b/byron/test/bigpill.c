inherit F_FOOD;
void create()
{
    set_name("超級大補丸", ({ "super big pill", "pill" }));
        set("unit", "顆");
    set("base_value", 999999);
        set("base_weight", 10);
        set("food_stuff", 10);                            // 食物量，食品一定要有食物量
    set("long", "吃了可以立即恢復你的魔力值(MP)體力值(HP)精力值(AP) 5000 點。\n");
    set("heal", ([
        "ap": 5000,
        "hp": 5000,
        "mp": 5000,
    ]) );
        setup();
}

