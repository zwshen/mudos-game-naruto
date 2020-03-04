#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIR"蠍蠍爪"NOR, ({ "double-scorpion claw","claw" }));
    set_weight(4500);
    setup_weapon(44, 55, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 53198);
        set("long", "地下沙穴裡蠍子所使用的武器。\n" );
    }
    set("apply_weapon/righthand", 
        ([ "str" : 3,            // 屬性：力量
           "attack" : 2,         // 攻擊力量
          
        ]) );
    setup();
}

