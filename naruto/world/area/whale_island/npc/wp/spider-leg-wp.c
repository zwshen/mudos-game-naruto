#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIK"大蜘蛛腿"NOR, ({ "spdier leg", "leg" }));
    set_weight(2000);
    setup_weapon(1, 5, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "根");
        set("value", 650);
        set("long", "一根剛斬下來的蜘蛛腿，但是摸起來毛茸茸，但也頗硬邦邦的，應該可以拿來打人。\n" );
    }

    setup();
}

