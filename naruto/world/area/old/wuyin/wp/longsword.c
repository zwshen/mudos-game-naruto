#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("細長劍", ({ "long sword","sword"}));
    set_weight(200);
    setup_weapon(1, 10, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 500);
        set("long", "輕型簡便的劍，極易攜帶，但殺傷力不夠高。");
    }
    setup();
}
