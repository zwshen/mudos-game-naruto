#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;

void create()
{
    set_name("¨ë¤ì¤M", ({ "thorn blade", "blade" }));
    set_weight(1000);
    setup_weapon(15, 15, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "§â");
        set("value", 1515);
        set("long", "¦³¨ë¤ì¦y¨ëªº¤ì¤M¡C\n" );
    }
    setup();
}
