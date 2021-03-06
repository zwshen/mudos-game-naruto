#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name(HIK"高原劍"NOR, ({ "gao yuan sword", "sword" }));
    set_weight(15000);
    setup_weapon(75, 90, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 167364);
        set("long", "一把細細長長的劍。\n" );
    }
    
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str" : 2,            // 屬性：力量
           "con" : 2,
           "wittiness" : 10,
           "intimidate" : 10,    // 攻擊技巧
    ]) );

    setup();
}
