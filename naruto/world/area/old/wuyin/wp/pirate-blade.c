#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name(RED"海賊彎刀"NOR, ({ "piriate's blade", "blade" }));
    set_weight(10000);
    setup_weapon(40, 50, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 14240);
        set("long", "古時候海盜身上配帶的短刃，可以把他拿來當匕首用。\n" );
    }
    
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "int" : 4,            // 屬性：力量
           "attack" : 5,         // 攻擊力量
           "intimidate" : 5,     // 攻擊能力
    ]) );

    setup();
}
