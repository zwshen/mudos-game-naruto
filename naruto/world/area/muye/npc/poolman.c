#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("泡湯人", ({ "man" }));
    set_race("human");
    set_level(10);
    
    set("long", "一個全身脫光光泡在池子裡的人。\n");
    set("camp", "muye");
    set("age", 21+random(30));
    set("gender", "male");
    
    // 一般時動作
    set("chat_chance", 1);
    set("chat_msg", ({
        (: command, "say 古代森林中的神木是一棵錯綜複雜的巨型樹木。" :),
        (: command, "say 聽說在古代森林裡住著一群擁有神奇法術的祭師。" :),
        (: command, "say 然而這些祭師擁有用神木製作的神劍。" :),
    }) );

    setup();
}
