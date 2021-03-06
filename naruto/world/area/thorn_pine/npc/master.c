#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

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
    exact = COMBAT_D->exact(this_object(), enemy, 1)*1.75;
    evade = COMBAT_D->evade(enemy, this_object(), 1) + COMBAT_D->wittiness(enemy, 1);

    this_object()->damage_stat("mp", 15, this_object());
    message_vision("\n$N將念集於雙掌，一團黃色的光芒愈來愈亮，忽然$N手一揮「"HIY"念氣波"NOR"」襲向$n！\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("$n簡單地運用魔力，輕鬆將$N的念力打散了。\n\n", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    if( enemy->query("guild") == "muya" ) raiseDamage = 400;
    else if( enemy->query("guild") == "hunter" ) raiseDamage = 250;
    else raiseDamage = 300;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
    add_temp("apply/attack", -raiseDamage);

    if( damage < 150 ) damage = 100 + random(50);

    enemy->receive_damage(damage, this_object());
    message_vision( sprintf("「轟！」地一聲，念氣在$n面前炸了開來，使$n受到一些傷害(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    return;
}
void create()
{
    set_name("豹念師", ({ "bow master", "master" }));
    set_race("human");
    set_level(35);
    set("gender", "male");
    set("age", 20+random(51));
    set("camp", "bow");
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "豹族人念師，平常負責祭祀、教學與指導。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"wp", "id":33, "amount":1, "p1":15, "p2":100 ]),  // 大木棒
        ([ "type":"wp", "id":34, "amount":1, "p1":5, "p2":100 ]),   // 鐵刀
        ([ "type":"wp", "id":42, "amount":1, "p1":1, "p2":100 ]),   // 刺木槍
        ([ "type":"wp", "id":30, "amount":1, "p1":1, "p2":200 ]),   // 突擊戰刀
    }) );
    setup();
}
int accept_fight(object ob)
{
    if( this_player()->query_temp("quest/villpk") < 1) {
        do_chat(({
           (: command, "sorry" :),
           (: command, "say 族長有令，平時一律不準打架" :),
        }));
        return 0;
    }
    return ::accept_fight(ob);
}