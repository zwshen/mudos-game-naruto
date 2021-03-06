#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name(YEL"山"HIY"峰"NOR"劍", ({ "shan feng sword", "sword" }));
    set_weight(10000);
    setup_weapon(75, 90, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 184864);
        set("no_box", 1);
        set("long", "劍身看似山峰，但是卻鋒利無比。\n" );
    }
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str" : 3,
           "dex" : 3,
           "wittiness" : 10,
           "intimidate" : 10,
    ]) );
    set("apply_weapon/lefthand", 
        ([ "str" : 1,
           "intimidate" : 10,
    ]) );
    setup();
}
