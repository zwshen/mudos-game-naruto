#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("寬劍"NOR, ({ "broad sword", "sword", "_FOUNDER_WP_" }));
    set_weight(8000);
    setup_weapon(5, 5, 100, 1);
    if( !clonep() ) {
        set("wield_as", "righthand");
        set("unit", "柄");
        set("value", 0);
        set("no_combine", 1);
        set("coal_need", 20);
        set("iron_need", 12);
        set("copper_need", 6);
        set("long", "寬刃劍，重量稍重，只適合拿在右手使用。\n" );
    }
    setup();
}
