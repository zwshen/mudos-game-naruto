#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name(YEL"巨人族之大槌"NOR, ({ "atlantean hammer", "hammer" }));
    set_weight(150000);
    setup_weapon(160, 200, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 540180);
        set("long", "巨人族所使用的超重戰槌，平常人根本很難舉起。\n" );
    }
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "intimidate" : 10,            // 屬性：力量
    ]) );
    setup();
}
