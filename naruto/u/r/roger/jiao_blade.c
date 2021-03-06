#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name(HIW"鮫肌"NOR, ({ "jiao ji blade", "blade" }));
    set_weight(15000);
    setup_weapon(160, 180, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "把");
        set("value", 636470);
        set("long", "霧隱村的忍刀七人眾之一「千柿鬼鮫」的愛刀。\n" );
    }
    
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str" : 7,            // 屬性：力量
           "exact" : 18,         // 命中能力
           "mp": 200,            // 增加MP
    ]) );

    setup();
}
