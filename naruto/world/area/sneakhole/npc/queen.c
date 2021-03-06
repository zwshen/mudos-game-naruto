#include <ansi.h>
#include <npc.h>

void do_fight()
{
    object enemy;
    int damage, raiseDamage, exact, evade;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    exact = COMBAT_D->exact(this_object(), enemy, 1)*2;
    evade = COMBAT_D->intimidate(enemy, 1) + COMBAT_D->wittiness(enemy, 1);

    this_object()->damage_stat("mp", 25, this_object());
    message_vision("\n$N"HIR"張大嘴巴一吐，居然噴出一團紅色液體！\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("$n向旁邊一跳，原地滋的一聲冒起黑煙，居然燒出了一個洞。\n\n", this_object(), enemy);
        this_object()->start_busy(1);
    } else {
        raiseDamage = 400;

        add_temp("apply/attack", raiseDamage); 
        damage = COMBAT_D->isDamage(this_object(), enemy, 0);
        add_temp("apply/attack", -raiseDamage);

        if( damage < 200 ) damage = 150 + random(50);

        enemy->receive_damage(damage, this_object());
        message_vision( sprintf("$n被液體噴到，皮膚居然慢慢潰爛，好像受到三度燒傷(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
        this_object()->start_busy(1);
        enemy->start_busy(2);
    }
    return;
}
void create()
{
    set_name(RED"蜘蛛皇后"NOR, ({ "queen spider", "spider" }) );
    set_race("beast");
    set("title","陰影蜘蛛");
    set_level(30);
    set("long", "身子比任何蜘蛛都還要巨大，眼睛中噴出紅光好像要將你生吞。\n");
    set("limbs", ({ "蜘頭", "身體", "腹部", "蛛腿" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":52, "amount":2, "p1":80, "p2":100 ]),       // 蜘蛛腿
        ([ "type":"obj", "id":81, "amount":1, "p1":80, "p2":100 ]),       // 蜘蛛標本
        ([ "type":"obj", "id":80, "amount":1+random(4), "p1":70, "p2":100 ]), // 黏液
        ([ "type":"food", "id":19, "amount":1, "p1":5, "p2":100 ]),       // 查克拉丸
        ([ "type":"eq", "id":91, "amount":1, "p1":1, "p2":300 ]),         // 開襠褲
        ([ "type":"eq", "id":92, "amount":1, "p1":1, "p2":100 ]),         // 蜘蛛脫殼
        ([ "type":"food", "id":17, "amount":1, "p1":5, "p2":100 ]),       // 體力丸
    }) );
    setup();
    add_temp("apply/attack", 50);
    set_skill("combat", 140);
    set_skill("dodge", 140);
    set_skill("parry", 140);
    set_skill("savage hit", 140);
    set_skill("heavy hit", 140);
    set_skill("continual hit", 140);
}