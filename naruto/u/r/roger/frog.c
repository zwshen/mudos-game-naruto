#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIG"文太"NOR, ({ "daemon frog", "frog" }) );
    set_race("beast");

    set_level(90);
    set("long", "一隻巨大無比的癩哈蟆，嘴裡還刁根煙管。\n");

    set("limbs", ({ "癩哈蟆頭", "身體", "腹部", "癩哈蟆腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );

    setup();
}
