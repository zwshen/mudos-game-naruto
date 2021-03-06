#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("蘑菇", ({ "agaric" }) );
    set_race("beast");
    set_level(1);

    set("long", "路邊的蘑菇你不要採。\n");

    set("limbs", ({ "菇頭", "菇根", "菇莖", "菇葉", "菇芽" }) );
    set("verbs", ({ "bite" }) );

    setup();
    // 削弱
    set_temp("apply/attack", -5);         // 攻擊力量
    set_temp("apply/defend", -5);         // 防禦力量
    set_temp("apply/exact", -5);          // 命中率
    set_temp("apply/evade", -5);          // 迴避率
    set_temp("apply/intimidate", -5);     // 攻擊能力
    set_temp("apply/wittiness", -5);      // 防禦能力

}
