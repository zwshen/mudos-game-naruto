#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(YEL"禪杖"NOR, ({ "buddhist monk's staff", "staff" }));
    set_weight(10000);
    setup_weapon(50, 55, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "把");
        set("value", 44452);
        set("long", "苦行僧或是雲遊僧人會隨身攜帶的長杖，特點是前端裝有環。\n" );
    }
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str" : 2,
           "savage hit" : 10,
    ]) );
    setup();
}
