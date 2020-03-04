#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIC"皮盾"NOR, ({ "shield" }));
    set_weight(6000);
    setup_weapon(0, 0, 100, 1);
    
    if( !clonep() ) {
        set("wear_as", ({ "lefthand" }) );
        set("unit", "個");
        set("value", 10000);
        set("long", "一個皮製盾牌，戰士們必備品。\n" );
    }
     // 附加能力
    set("apply_weapon/lefthand",
        ([ "armor": 5,
    ]) );

   
      setup();
}


