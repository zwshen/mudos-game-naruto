#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("細劍"NOR, ({ "thin sword", "sword", "_FOUNDER_WP_" }));
    set_weight(500);
    setup_weapon(2, 4, 100, 1);
    if( !clonep() ) {
        set("wield_as", "lefthand");
        set("unit", "把");
        set("value", 0);
        set("no_combine", 1);
        set("coal_need", 12);
        set("iron_need", 6);
        set("copper_need", 20);
        set("long", "尖細短小，看起來不是很精美的小劍，適合左手使用。\n" );
    }
    setup();
}
