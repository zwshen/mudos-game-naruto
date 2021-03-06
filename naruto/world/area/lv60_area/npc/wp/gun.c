#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

string *combat_wp = ({
    "$N單手持槍，使用交互射擊的技巧，連續不斷的發射子彈攻擊$n$l",
    "$N故意改用衝擊力較強的火繩發射$w彈，企圖對$n的$l造成重創",
    "$N躲到掩蔽物後方進行填彈，同時拿出備藏副槍射擊$n腳踝阻止行動",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

int i=1;

void create()
{
    set_name("種子島"REV"鐵砲"NOR, ({ "germ gun", "gun" }));
    set_weight(3000);
    setup_weapon(25, 80, 100, 1);

    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 50000);
        set("no_box", 1);
        set("no_auc", 1);
        set("have_mag", 1);
        set("long", "日本鐵砲的始祖，也是經由改良後的重要武器之一，原本因為裝備火\n"
                    "繩而使得裝彈速度不夠快，無法達到使用的成果，但是經由種子島家\n"
                    "改良後，現在已經衍生出許多鐵砲戰法了。\n" );
    }
    set("apply_weapon/righthand", 
        ([ "int" : 5,             // 智慧
           "defend" : 20,         // 防禦能力
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

    if( arg == this_object()->query("id")+".loose" ) {

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
        exact = COMBAT_D->intimidate(me, 1)*1.2;
        evade = COMBAT_D->intimidate(enemy, 1);

        me->damage_stat("mp", 20, me);
        message_vision("\n$N將火管塞進"+query("name")+"擺出射擊姿態『"HIK"三段速射"NOR"』對$N第"+chinese_number(i)+"次攻擊！\n", me, enemy);
        if( !COMBAT_D->SkillHit(me, enemy, exact, evade) ) {
            message_vision("$N瞄的不夠準確，最終還是沒有擊中$n。\n\n", me, enemy);
            i += 1;
        } else {
            if( userp(me) ) raiseDamage = me->query_level()*2;
            else raiseDamage = me->query_level()*5;

            me->add_temp("apply/attack", raiseDamage); 
            damage = COMBAT_D->isDamage(me, enemy, this_object());
            me->add_temp("apply/attack", -raiseDamage);

            if( damage > 600 ) damage = 600;
            if( damage < 150 ) damage = 150;

            enemy->receive_damage(damage, me);
            message_vision( sprintf("$n被鐵砲所擊中，留下一個手指般寬度的小彈孔傷害(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), me, enemy);
            i += 1;
        } if( i >= 4 ) {
            message_vision(CYN"$N"CYN"連續射擊了三次，必須稍微休息才能繼續射擊。\n\n"NOR, me, enemy);
            i = 1;
            me->start_busy(3);
        }
        return 1;
    }
}