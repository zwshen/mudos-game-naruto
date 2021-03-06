#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name(HIW"脊骨劍"NOR, ({ "spinal sword", "sword" }));
    set_weight(7000);
    setup_weapon(90, 110, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "把");
        set("value", 180300);
        set("long", "從脊椎骨拔出來的長骨劍，上面沾滿鮮血看來非常可怕。\n" );
    }
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str": 4,
           "attack": 10,
           "intimidate": 10,
           "heavy hit": 10,
    ]) );
    setup();
}
