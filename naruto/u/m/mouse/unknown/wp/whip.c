#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name("皮鞭", ({ "whip" }));
    set_weight(800);
    setup_weapon(20, 20, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "條");
        set("value", 3220);
        set("long", "平常用來鞭打動物的鞭子。\n" );
    }
    // 附加能力
    set("apply_weapon/righthand",
        ([ "con" : 1,
           "hp" : 10,
    ]) );
    setup();
}
