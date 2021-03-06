#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(HIY"神木劍"NOR, ({ "Tree sword", "sword" }));
    set_weight(7000);
    setup_weapon(50, 80, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "righthand", "lefthand" }) );
        set("unit", "把");
        set("value", 73230);
        set("long", "神木樹枝所成之劍，鋒利無比，劍上微閃著光芒。\n" );
        set("wield_msg", HIW"$N「刷」的一聲抽出$n"HIW"，微微的亮光在$n"HIW"四周閃耀著。\n"NOR);
        set("unwield_msg", "$N將$n收回劍鞘，光芒也漸漸淡去。\n");
    }
    // 附加能力
    set("apply_weapon/righthand", 
        ([ "str" : 2,            // 屬性：力量
           "attack" : 10,         // 攻擊力量
           "intimidate" : 5,     // 攻擊能力
           "continual hit" : 7,
    ]) );
    set("apply_weapon/lefthand", 
        ([ "intimidate" : 5,     // 攻擊能力
    ]) );
    setup();
}
