#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N張開$w嘶吼一聲，快速地朝$n$l招呼過去",
    "$N$w上發出一道閃光，以肉眼無法辨識的速度擊向$n$l",
    "$N利用自己的身子將$n包圍，雙爪不斷地攻擊$n",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name("龍爪", ({ "dragon claw", "claw" }));
    set_weight(8000);
    setup_weapon(40, 55, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "支");
        set("value", 47094);
        set("have_mag", 1);
        set("long", "念龍能力夠強時所擁有的利爪。\n" );
    }
    setup();
}