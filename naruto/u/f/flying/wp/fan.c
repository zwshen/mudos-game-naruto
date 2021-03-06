#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name(HIB"巨扇"NOR, ({ "big fan", "fan" }));
    set_weight(15000);
    setup_weapon(45, 55, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "twohanded" }) );
        set("unit", "把");
        set("value", 127100);
        set("long", "手鞠的專用武器，可以配合忍術捲起巨大的沙塵和使用忍術．\n"
                    "鎌鼬，並且相當堅固，可以當作防禦性武器使用。\n" );
    }
    
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "int" : 5,            // 屬性：力量
           "con" : 5,            // 攻擊能力
    ]) );

    setup();
}

