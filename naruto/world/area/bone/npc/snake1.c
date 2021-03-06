#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

void do_fight()
{
    int damage, raiseDamage, exact, evade;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( this_object()->query_temp("quest/snake_blade") == 1) return;

    exact = COMBAT_D->intimidate(this_object(), 1)*2;
    evade = COMBAT_D->wittiness(enemy, 1);

    this_object()->damage_stat("mp", 1, this_object());
    message_vision("\n$N"HIG"拿著彎刀朝地上一掃，捲起地上草皮石塊攻擊"NOR"$n"HIG"。\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("$n將石塊草皮通通撥開，絲毫不受影響繼續攻擊$N。\n\n", this_object(), enemy);
        return;
    }
    raiseDamage = 50;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
    add_temp("apply/attack", -raiseDamage);

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);

    enemy->receive_damage(damage, this_object());
    this_object()->add_temp("quest/snake_blade", 1);
    message_vision( sprintf("石塊打的$n手忙腳亂，不少地方都被砸傷(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    call_out("blade_1", 5, this_object());
    return;
}

void blade_1(object me)
{
    int damage, raiseDamage, exact, evade;
    object enemy;

    enemy = me->query_opponent();

    me->delete_temp("quest/snake_blade");

    if( !enemy ) return;
    if( environment(me)->is_area() ) {
        if( !area_environment(me, enemy) ) return;
    } else {
        if( environment(enemy) != environment(me) ) return;
    }
    if( !me->is_fighting(enemy) ) return;

    exact = COMBAT_D->intimidate(this_object(), 1);
    evade = COMBAT_D->wittiness(enemy, 1);

    me->damage_stat("mp", 15, me);
    message_vision("\n$N"HIY"從捲起的石塊草皮中順勢由下而上朝$n的要害劈出一記狠招！\n"NOR, me, enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("但是$n這次已經發現了$N的企圖，輕鬆地將$N的攻擊格開了。\n\n"NOR, me, enemy);
        return;
    }
    raiseDamage = 450;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(me, enemy, 0);
    add_temp("apply/attack", -raiseDamage);

    if( damage < 150 ) damage = 100 + random(50);

    enemy->receive_damage(damage, me);
    message_vision( sprintf("$n依然逃不過$N的攻擊，但這次卻是被彎刀劈中胸膛，造成嚴重的砍傷(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), me, enemy);
    return;
}

void create()
{
    set_name("戰蛇", ({ "warrior snake", "snake" }) );
    set_race("human");
    set("gender", "male");
    set_level(33+random(3));
    set("age", 15+random(21));
    set("limbs", ({ "蛇頭", "蛇尾", "腹部", "胸口", "腳部", "肩膀", "腰部" }) );
    set("title",HIG"蛇族戰士"NOR);
    set("long", "手持彎刀，拿著一柄圓形劍盾的蛇人。\n");
    set("camp", "snaker");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "say 殺！不留活口！" :),
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"eq", "id":87, "amount":1, "p1":1, "p2":100 ]),     // 蛇神項鍊
        ([ "type":"wp", "id":49, "amount":1, "p1":1, "p2":300 ]),     // 彎刀
        ([ "type":"wp", "id":48, "amount":1, "p1":1, "p2":275 ]),     // 盾劍
        ([ "type":"food", "id":30, "amount":1, "p1":35, "p2":100 ]),  // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":35, "p2":100 ]),   // 蛇皮
        ([ "type":"wp", "id":14, "amount":1, "p1":30, "p2":100 ]),    // 蛇牙
        ([ "type":"obj", "id":82, "amount":1, "p1":20, "p2":100 ]),   // 蛇毒
    }) );
    setup();
}