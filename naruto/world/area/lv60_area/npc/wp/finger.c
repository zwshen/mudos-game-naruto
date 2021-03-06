#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N掌風呼嘯而過，挾帶著猛烈的火燄直撲$n的$l",
    "$N運用手腕的技巧使$w碰撞發出火花，只聽見「鏗」地一聲，火蛇竄向$n$l",
    "$N兩手$w磨擦發出火光同時，$N捏拳成爪掃向$n的$l",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name("吳氏"HIR"妖炎指"NOR, ({ "wu fire finger", "finger" }));
    set_weight(3000);
    setup_weapon(25, 30, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "對");
        set("value", 50000);
        set("no_box", 1);
        set("no_auc", 1);
        set("have_mag", 1);
        set("long", "吳氏一族所使用的兵器，指環的前端是能夠磨擦出火燄的高耐磨材質\n"
                    "物，製造方式只有吳氏一族的人才知道，是不傳的密術。使用此戒便\n"
                    "能在攻擊時放出火燄燒傷對手。\n" );
    }
    set("apply_weapon/twohanded", 
        ([ "exact" : 60,         // 命中能力
    ]) );
    setup();
}
void init()
{
    add_action("do_perform", "perform");
}
int do_perform(string arg)
{
    mapping cnd = ([]);
    object enemy, me;
    int exact, evade;

    me = this_player();
    enemy = this_player()->query_opponent();

    if( arg == this_object()->query("id")+".fire" ) {

        if( me->is_busy() ) return notify_fail("你現在沒有空。\n");
        if( !enemy ) return notify_fail("沒有敵人可以施展技能。\n");
        if( !me->is_fighting(enemy) ) return notify_fail("你並未和對方戰鬥。\n");
        if( me->query_stat("mp") < 20 ) return notify_fail("你沒魔力使用這招。\n");
        if( enemy->query_condition("firedamage", 1) != 0) return notify_fail("對方已經著火，不用燒了。\n");
        if( !query("equipped") ) return notify_fail("你沒裝備這樣武器。\n");
        if( me->query_level() < 41 ) return notify_fail("你無法使用這個招式。\n");

        // 敵人在不同位置
        if( environment(me)->is_area() ) {
            if( !area_environment(me, enemy) ) return notify_fail("沒有敵人可以施展技能。\n");
        } else {
            if( environment(enemy) != environment(me) ) return notify_fail("沒有敵人可以施展技能。\n");
        }
        exact = COMBAT_D->intimidate(me, 1)*1.5;
        evade = COMBAT_D->wittiness(enemy, 1);

        me->damage_stat("mp", 20, me);
        message_vision("\n$N大喝一聲「吳氏─"HIR"妖炎拳"NOR"」只見$N雙手噴出火燄拍向$n！\n", me, enemy);
        if( !COMBAT_D->SkillHit(me, enemy, exact, evade) ) {
            message_vision("結果攻擊被$n給視破了，沒有達到效果。\n\n", me, enemy);
            me->start_busy(2);
        } else {
            message_vision("結果攻擊擊中了$n的身子，火燄快速地燃燒了起來！\n\n", me, enemy);
            me->start_busy(1);

            cnd["name"] = HIR+"著火狀態"+NOR;
            cnd["duration"] = 5;
            cnd["from"] = me;

            enemy->set_condition("firedamage", cnd);
        }
        return 1;
    }
}