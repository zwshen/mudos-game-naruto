#include <ansi.h>
#include <weapon.h>
inherit F_WEAPON;
void create()
{
    set_name(HIW"狼煙戟"NOR,({"wolf fume halberd","halberd"}));;
    set_weight(15000);
    setup_weapon(150, 180, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "支");
        set("value", 800000);
        set("long",HIW"赦生道守路者 赦生童子所專屬的武器\n"
                      "也是退休的狼王逃山補劍缺所打造的武器。\n"NOR);
}
    set("apply_weapon/twohanded", 
        ([ "str"   : 1,            
           "con"   : 1,
           "dex"   : 1,
           "int"   : 1,
              
    ]) );
    setup();
}

