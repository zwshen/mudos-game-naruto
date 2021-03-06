#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N將$w展開，右手靈巧的控制$w上的風貝，一道銳利的彈丸射向$n$l",
    "$N利用了$w的彈性與角度落差，以拋物線的方式射出彈丸砸向$n頭部",
    "$N先射出兩枚石頭鎖住$n行動位置，然後將彈丸直接瞄準$n$l射出",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name(HIG"兜弓"NOR, ({ "du bow", "bow", "_CATAPULT_" }));
    set_weight(8000);
    setup_weapon(80, 80, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("no_box", 1);
        set("value", 51320);
        set("have_mag", 1);
        set("long", "強化過的大型彈弓，又稱為「獨角仙」。\n" );
    }
    set("apply_weapon/twohanded", 
        ([ "dex" : 5,
           "exact" : 30,
    ]) );
    setup();
}
