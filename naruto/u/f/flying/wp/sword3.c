#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIC"雷神之劍"NOR, ({ "Thunder-god sword", "sword" }));
    set_weight(6000);
    setup_weapon(180, 200, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 1105360);
        set("long", "傳說中第二代火影所用過的刀 雷神之劍。\n" );
    }
     // 附加能力
        set("apply_weapon/righthand",
        ([ "str" : 10,            // 屬性：力量
 ]) );
        set("apply_weapon/lefthand",
        ([ "str" : 10,            // 屬性：力量
 ]) );
    
      setup();
}


