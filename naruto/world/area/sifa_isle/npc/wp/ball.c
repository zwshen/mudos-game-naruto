#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("鐵球", ({ "iron ball", "ball" }));
    set_weight(50000);
    setup_weapon(40, 40, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 4740);
        set("long", "沉重的大鐵球，上面還畫著海軍的標誌。\n" );
    }
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "str" : 1 ]) );
    setup();
}
