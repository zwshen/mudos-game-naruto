#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N駕地一聲，拍動跨下的馬匹，快速衝向$n身前以$w橫掃攻擊$n顏面",
    "$N先格開了$n的攻擊，順勢靈活地操縱馬匹，從旁側擊$n的$l",
    "$N控制馬匹先退後數尺，隨著馬匹一聲長鳴，開始快速衝向$n進行衝擊",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

int i=1;

void create()
{
    set_name("武田"HIR"馬上槍"NOR, ({ "takeda lance", "lance" }));
    set_weight(3000);
    setup_weapon(70, 100, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "righthand", "twohanded" }) );
        set("unit", "柄");
        set("value", 50000);
        set("no_box", 1);
        set("no_auc", 1);
        set("have_mag", 1);
        set("long", "武田家族所使用的武器，樣式有點類似戟，通常使用於騎馬時，因為\n"
                    "材質是以純度很高的鐵器所製成，所以以步兵模式使用這把武器會感\n"
                    "覺有些力不從心。\n" );
    }
    set("apply_weapon/twohanded", 
        ([ "con" : 2,             // 體質
           "hp" : 100,            // 生命
           "ap" : 50              // 精神
    ]) );
    set("apply_weapon/righthand", 
        ([ "hp" : 200,            // 生命
           "ap" : 100             // 精神
    ]) );
    setup();
}
void init()
{
    add_action("do_perform", "perform");
}
int do_perform(string arg)
{
    int damage, raiseDamage, exact, evade;
    object enemy, me;

    me = this_player();
    enemy = this_player()->query_opponent();

    if( arg == this_object()->query("id")+".lunge" ) {

        if( me->is_busy() ) return notify_fail("你現在沒有空。\n");
        if( !enemy ) return notify_fail("沒有敵人可以施展技能。\n");
        if( !me->is_fighting(enemy) ) return notify_fail("你並未和對方戰鬥。\n");
        if( !query("equipped") ) return notify_fail("你沒裝備這樣武器。\n");
        if( me->query_stat("mp") < 20 ) return notify_fail("你沒魔力使用這招。\n");
        if( me->query_level() < 41 ) return notify_fail("你無法使用這個招式。\n");

        // 敵人在不同位置
        if( environment(me)->is_area() ) {
            if( !area_environment(me, enemy) ) return notify_fail("沒有敵人可以施展技能。\n");
        } else {
           if( environment(enemy) != environment(me) ) return notify_fail("沒有敵人可以施展技能。\n");
        }
        exact = COMBAT_D->wittiness(me, 1)*1.3;
        evade = COMBAT_D->intimidate(enemy, 1);

        me->damage_stat("mp", 20, me);
        message_vision("\n$N揮舞著"+query("name")+"騎在威風的戰馬上「"GRN"萬馬奔騰"NOR"•"YEL"崩乘"NOR"」使盡全力衝擊$n！\n", me, enemy);
        if( !COMBAT_D->SkillHit(me, enemy, exact, evade) ) {
            message_vision("$N衝著衝著一不小心居然衝過了頭，剛才的氣勢完全遜掉了。\n\n", me, enemy);
            me->start_busy(3);
        } else {
            if( userp(me) ) raiseDamage = me->query_level()*3 + me->query_skill("combat");
            else { 
                if( enemy->query_stat_maximum("hp") > 10000 ) raiseDamage = 500;
                if( enemy->query_stat_maximum("hp") > 1000 ) raiseDamage = enemy->query_stat_current("hp")/10;
                else raiseDamage = 300;
            }
            me->add_temp("apply/attack", raiseDamage); 
            damage = COMBAT_D->isDamage(me, enemy, this_object());
            me->add_temp("apply/attack", -raiseDamage);

            if( damage < 150 ) damage = 100 + random(50);

            enemy->receive_damage(damage, me);
            message_vision( sprintf("$n「磅噹」一聲悶響，被戰馬撞飛了出去，受到一些內傷(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), me, enemy);
            me->start_busy(1);
            enemy->start_busy(2);
        }
        return 1;
    }
}