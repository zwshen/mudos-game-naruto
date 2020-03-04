#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("手術刀", ({ "scalpel" }));
    set_weight(8000);
    setup_weapon(40, 55, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 47094);
        set("long", "相當小巧的刀子，但是卻十分的鋒利。\n" );
    }

    setup();
}

