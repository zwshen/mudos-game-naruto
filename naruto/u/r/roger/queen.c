#include <ansi.h>
#include <npc.h>

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_fight()
{
    object enemy;
    int damage;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    damage = random(this_object()->query_ability("attack") + this_object()->query_ability("intimidate")) + random(50) + 50;
    damage -= random(enemy->query_ability("defend") + enemy->query_ability("wittiness"));
    message_vision("$N"HIR"張大嘴巴一吐，居然噴出一團紅色液體！\n"NOR, this_object(), enemy);
    if( damage <= 0 || random(enemy->query_ability("intimidate")) > 100) {
        message_vision("        $n向旁邊一跳，原地滋的一聲冒起紫煙。(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    enemy->damage_stat("hp", damage, this_object());
    message_vision("        $n被液體噴到，覺得全身好像受到三度燒傷。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
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
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":52, "amount":2, "p1":80, "p2":100 ]),       // 蜘蛛腿
        ([ "type":"obj", "id":81, "amount":1, "p1":80, "p2":100 ]),       // 蜘蛛標本
        ([ "type":"obj", "id":80, "amount":1+random(4), "p1":70, "p2":100 ]), // 黏液
        ([ "type":"food", "id":19, "amount":1, "p1":5, "p2":100 ]),       // 查克拉丸
        ([ "type":"eq", "id":91, "amount":1, "p1":1, "p2":600 ]),         // 開襠褲
        ([ "type":"eq", "id":92, "amount":1, "p1":5, "p2":100 ]),         // 蜘蛛脫殼
        ([ "type":"food", "id":17, "amount":1, "p1":5, "p2":100 ]),       // 體力丸
    }) );
    setup();
    set_skill("combat", 120);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("savage hit", 120);
    set_skill("heavy hit", 120);
    set_skill("continual hit", 120);
}
