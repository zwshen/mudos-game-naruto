#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N發動「"HIB"冷氣泡"NOR"」讓$n的身體感覺一陣冰冷，居然被凍傷了",
    "$N將$w一轉丟出「"YEL"電氣泡"NOR"」啪嘰一聲電的$n哇哇大叫",
    "$N吹出一顆紅通通的「"HIR"熱氣泡"NOR"」燙的$n的$l都起了一個大水泡",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name(HIC"天候棒"NOR, ({ "sky stick", "stick", "_WEATHER_" }));
    set_weight(2000);
    setup_weapon(75, 90, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("no_box", 1);
        set("value", 81740);
        set("have_mag", 1);
        set("long", "騙人布利用「貝」所製作的新一代天候棒，威力強大。\n" );
    }
    set("apply_weapon/twohanded", 
        ([ "con" : 1,
           "dex" : 3,
           "int" : 1,
           "armor" : 30,
    ]) );
    setup();
}
