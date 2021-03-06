#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name(HIK"和道"HIW"一文字"NOR, ({ "beta katana", "katana" }));
    set_weight(15000);
    setup_weapon(170, 190, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("no_box", 1);
        set("value", -1);
        set("long", "背負著重要記憶的索隆愛刀，有著必須與夢想共同進退的意志。\n" );
    }
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "str": 10,
           "attack": 30,
           "evade": 15,
           "exact": 15,
           "continual hit": 10,
    ]) );
    setup();
}
