#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("迴旋斧", ({ "whirls axe", "axe" }));
    set_weight(3000);
    setup_weapon(25, 30, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 3477);
        set("long", "一把短斧，傷害較為固定。\n" );
    }
    set("apply_weapon/twohanded", 
        ([ "intimidate" : 5,
    ]) );
    setup();
}
