#include <npc.h>
#include <ansi.h>

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
    int damage;
    object enemy;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("$N"HIY"身出爪子一巴掌打向"NOR"$n"HIY"！\n"NOR, this_object(), enemy);
    damage = 20+random(36);
    if( random(enemy->query_ability("evade")) > 100) {
        message_vision("        $n身子蹲低避開了攻擊。(0)"+report_status(enemy)+"", this_object(), enemy);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        「啪」地一聲，打的$n滿天全金條, 要抓沒半條。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    return;
}
void create()
{
    set_name("羶熊", ({ "sin bear", "bear", "_SIN_BEAR_" }) );
    set_race("beast");
    set_level(28+random(3));
    set("age", 10+random(51));
    set("limbs", ({ "熊頭", "熊尾", "熊腳", "胸口", "腿部", "熊掌" }) );
    set("title",HIY"馴獸"NOR);
    set("long", "頭上長了兩隻怪角的巨大熊類，是蛇族騎士的座騎。\n");
    set("attitude", "aggressive");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":23, "amount":1, "p1":50, "p2":100 ]),   // 熊毛
        ([ "type":"food", "id":21, "amount":1, "p1":5, "p2":100 ]),   // 熊掌
        ([ "type":"eq", "id":65, "amount":1, "p1":5, "p2":100 ]),     // 熊大衣
    }) );
    setup();
}
