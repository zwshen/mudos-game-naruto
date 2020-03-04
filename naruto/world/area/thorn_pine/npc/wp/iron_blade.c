#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("鐵刀", ({ "iron blade", "blade" }));
    set_weight(1000);
    setup_weapon(10, 15, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 2424);
        set("long", "鐵製的刀，一般武器。\n" );
    }
    setup();
}
