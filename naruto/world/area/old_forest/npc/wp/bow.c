#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIW"弓"NOR, ({ "bow" }));
    set_weight(5000);
    setup_weapon(15, 15, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "把");
        set("value", 1515);
        set("long", "一把很普通的弓。\n" );
    }
    setup();
}
