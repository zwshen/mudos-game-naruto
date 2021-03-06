#include <npc.h>

void create()
{
    set_name("大蛇王", ({ "the king of snake", "snake" }) );
    set_race("beast");
    set_level(22);

    set("long", "一隻蛇中之王，看起來就是不好惹。\n");

    set("limbs", ({ "蛇頭", "蛇尾", "腹部" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 主動攻擊

    set("set_drop", ({
        ([ "type":"food", "id":29, "amount":1, "p1":35, "p2":100 ]),   // 蛇蛋
        ([ "type":"food", "id":30, "amount":1, "p1":25, "p2":100 ]),   // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":25, "p2":100 ]),   // 蛇皮
    }) );

    setup();

    if( random(100) > 70 ) carry_object(__DIR__"wp/snake_tooth.c")->wield("righthand");
}
