#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("鐵刃", ({ "blade" }));
    set_weight(20000);
    setup_weapon(1, 10, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 500);
        set("long", "以生鐵所打造的刀，不是很精緻，力量不高 。");
    }
    setup();
}
