#include <npc.h>

inherit F_BANDIT;

void create()
{
    set_name("攔路強盜", ({ "road rage bandit", "bandit" }) );
    set("unit", "位");
    set("gender", "male");
    set_level(20);
    set("age", 18+random(60));
    set("long", "一臉就像欠他幾十萬一樣，看起來不好惹。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "攔路強盜狠狠的「呸！」地一聲後轉頭盯著你猛瞧...\n",
        "攔路強盜「哼」地一聲...\n",
    }));

    // 守著出口
    set("guard_exit", ({ "east", "west" }));

    setup();
}

int do_guard_exit(int x, int y, string exit)
{
    message_vision("$n將$N擋住。\n", this_player(), this_object());
    return 1;
}