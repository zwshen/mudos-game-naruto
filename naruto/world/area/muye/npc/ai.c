#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("愛子小姐", ({ "ai zi", "zi" }));
    set_race("human");
    set_level(5);
    set("camp", "muye");
    set("long", "愛子小姐看起來愁眉苦臉的，好像有什麼煩惱一樣。\n");

    set("age", 23);
    set("gender", "female");
    
    // 一般時動作
    set("chat_chance", 1);
    set("chat_msg", ({
        (: command, "say 都怪那園丁辭職了！害後院亂七八糟的。" :),
    }) );

    setup();
}
