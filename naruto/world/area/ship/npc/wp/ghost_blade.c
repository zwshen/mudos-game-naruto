#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIM"纯颔"HIY"过"NOR, ({ "tiger katana", "katana" }));
    set_weight(5000);
    setup_weapon(100, 120, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "lefthand" }) );
        set("unit", "р");
        set("no_box", 1);
        set("value", 176010);
        set("long", "め过┮ラ硑ō海獹籔畉ぃ环\n" );
    }
    set("apply_weapon/lefthand",
        ([ "str" : 3,
           "exact" : 5,
           "intimidate" : 5,
    ]) );
    setup();
}
