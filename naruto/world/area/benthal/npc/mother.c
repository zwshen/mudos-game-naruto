#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("魚婆", ({ "fish mother", "mother" }) );
    set_race("human");
    set_level(8);
    set("gender", "female");
    set("age", 37);
    set("long", "跟隨魚公一起離群而居，不知道她離群而居是什麼原因？\n");
    setup();
}
