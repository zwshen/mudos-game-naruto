#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N拉起$w瞄準$n的$l用力一彈，射出一枚彈丸",
    "$N抓了一把石頭放在$w上往$n彈去，一堆碎石頭直接射向$n",
    "$N以飛快的速度連續拿出三顆彈丸彈出射向$n",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name("彈弓", ({ "catapult", "_CATAPULT_" }));
    set_weight(2000);
    setup_weapon(1, 3, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 202);
        set("have_mag", 1);
        set("long", "騙人布做的小彈弓，看起來還不錯用。\n" );
    }
    setup();
}
