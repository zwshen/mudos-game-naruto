#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("鐵球鎖鏈", ({ "iron ball enchain", "enchain" }));
    set_weight(50000);
    setup_weapon(40, 120, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 40780);
        set("long", "沉重的鐵球，前端拉著一條鎖鍊。\n" );
    }
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "str" : 1 ]) );
    setup();
}
