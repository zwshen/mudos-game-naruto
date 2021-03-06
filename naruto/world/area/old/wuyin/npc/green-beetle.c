#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("綠瓢蟲", ({ "green beetle","beetle"  }) );
    set_race("beast");
    set_level(1);

    set("long", "一隻巨型的瓢蟲，可愛的模樣看起來是善意的爬蟲類。\n");

    set("limbs", ({ "頭部", "身體", "背殼", "觸角" }) );
    set("verbs", ({ "bite" }) );

    setup();

    // 削弱
    set_temp("apply/attack", -5);         // 攻擊力量
    set_temp("apply/defend", -5);         // 防禦力量
    set_temp("apply/exact", -5);          // 命中率
    set_temp("apply/evade", -5);          // 迴避率
    set_temp("apply/intimidate", -5);     // 攻擊能力
    set_temp("apply/wittiness", -5);      // 防禦能力

    if( random(100) > 80 ) carry_object("/world/area/wuyin/eq/bug-armor.c");
    if( random(100) > 60 ) carry_object("/world/area/wuyin/obj/honey.c");
}
