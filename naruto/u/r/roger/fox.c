#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIR"九尾狐"NOR, ({ "demon fox", "fox" }) );
    set_race("beast");

    set_level(99);
    set("long", "一隻擁有九條尾巴的狐狸，週身燃起熊熊妖火，似乎要把你給熔了。\n");

    set("limbs", ({ "狐頭", "身體", "腹部", "狐腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );

    setup();
}
