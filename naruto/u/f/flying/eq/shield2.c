#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("皮盾", ({ "shield" }));
    set_weight(15000);
    setup_weapon(5, 10, 0, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "lefthand" }) );
        set("unit", "個");
        set("value", 5000);
        set("long", "一個皮製圓盾。\n" );
    }
    
    // 附加能力
    set("apply_weapon/lefthand", 
        ([ "con" : 3,            // 屬性：力量
           "armor" : 5,         // 攻擊力量
           "wittiness" : 5,     // 攻擊能力   
 ]) );

    setup();
}

