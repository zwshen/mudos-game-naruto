#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("紅瓢蟲", ({ "red beetle","beetle"  }) );
    set_race("beast");
    set_level(15);

    set("long", "一隻巨型的瓢蟲，原來和綠瓢蟲都是同一個種族的。\n");

    set("limbs", ({ "頭部", "身體", "背殼", "觸角" }) );
    set("verbs", ({ "bite" }) );

    setup();

    if( random(100) > 60 ) carry_object("/world/area/wuyin/obj/honey.c");
    if( random(100) > 60 ) carry_object("/world/area/wuyin/obj/honey.c");
}
