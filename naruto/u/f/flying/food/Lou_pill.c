inherit F_FOOD;

void create()
{
    set_name("正露丸", ({ "Positive Lou pill", "pill" }));
    set("unit", "顆");
    set("base_value", 600);
    set("base_weight", 10);
    set("food_stuff", 1);              // 食物量，食品一定要有食物量
    set("long", "全家大小，出門旅行，必備良藥。\n");
    set("heal", ([
        "ap": 9999,
        "hp": 9999,
        "mp": 9999,


    ]) );
        setup();
}

