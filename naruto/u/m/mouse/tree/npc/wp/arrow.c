#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("½b", ({ "arrow" }));
    set_weight(1000);
    setup_weapon(10, 15, 150, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "lefthand" }) );
        set("unit", "®Ú");
        set("value", 1212);
        set("long", "¤}©Ò¥Îªº½b¦Ð¡C\n" );
    }
    setup();
}
