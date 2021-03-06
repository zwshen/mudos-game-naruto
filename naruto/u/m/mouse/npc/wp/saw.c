#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

void create()
{
    set_name(HIY"電"HIW""BLK"鋸"NOR, ({ "An Electroc Saw", "saw" }));
    set_weight(15000);
    setup_weapon(100, 150, 200, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "twohanded" }) );
        set("unit", "柄");
        set("value", 10);
        set("long", "一柄威力強大的電鋸，任何的東西都經不起它一鋸。\n" );
        set("wield_msg", "$N拿起$n的手把拉了幾下，忽然$n發出轟轟的聲音並開始轉動。\n");
        set("unwield_msg", "$n聲音漸漸消失，$n的轉動也停止了。\n");
    }
    // 附加能力
    set("apply_weapon/righthand", // 左手適用
        ([ "str" : 10,            // 屬性：力量
           "attack" : 10,         // 攻擊力量
           "intimidate" : 10,     // 攻擊能力
    ]) );
    set("apply_weapon/twohanded", // 雙手適用
        ([ "str" : 10,            // 屬性：力量
           "attack" : 20,         // 攻擊力量
           "intimidate" : 20,     // 攻擊能力
    ]) );
    setup();
}
