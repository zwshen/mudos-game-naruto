#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("刻紋劍", ({ "lines sword", "sword" }));
    set_weight(2000);
    setup_weapon(15, 15, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "把");
        set("value", 9715);
        set("long", "上面刻有紋路的劍，比一般武器精緻。\n" );
    }
    set("apply_weapon/righthand", 
        ([ "con" : 1,
           "armor" : 5,
    ]) );
    setup();
}
