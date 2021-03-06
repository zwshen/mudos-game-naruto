#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name(HIY"斬首刀"NOR, ({ "jhan shou blade", "blade" }));
    set_weight(15000);
    setup_weapon(100, 130, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "twohanded" }) );
        set("unit", "把");
        set("value", 365230);
        set("long", "忍刀七人眾，霧隱村逃亡忍者再不斬的愛刀，再不斬曾利用自己異於\n"
                    "常人腕力將斬首刀當作飛行道具使用。\n" );
    }
    
    // 附加能力
    set("apply_weapon/twohanded", 
        ([ "str" : 5,            // 屬性：力量
           "attack" : 5,         // 攻擊力量
           "intimidate" : 10,     // 攻擊能力
    ]) );

    setup();
}


