#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIG"青龍"NOR, ({ "green dragon sword", "sword" }));
    set_weight(5000);
    setup_weapon(100, 120, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "lefthand" }) );
        set("unit", "把");
        set("value", 176010);
        set("long", "『左青龍，右白虎』的青龍劍。\n" );
    }

    set("apply_weapon/lefthand", 
        ([ "dex" : 10,
           "evade" : 10,
           "wittiness" : 10,
           "mp": 8000,            // 增加MP
           "hp": 8000,            // 增加HP
           "ap": 8000,            // 增加AP
 
    ]) );

    setup();
}


