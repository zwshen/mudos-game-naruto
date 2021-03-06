#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

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
    message_vision("$N"HIR"偷偷摸摸的轉換位置，忽然從草中跳出偷襲"NOR"$n"HIK"！\n"NOR, this_object(), enemy);
    damage = random(this_object()->query_ability("exact") + this_object()->query_ability("intimidate")) + random(50);
    damage -= random(enemy->query_ability("evade"));
    if( damage <= 0 || random(enemy->query_ability("evade")) > 190) {
        message_vision("        $n視破了$N的偷襲，避開了攻擊。(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->delete_temp("quest/snake_blade");
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        $n被刀刺了一下卻找不到$N從何處攻擊。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    this_object()->add_temp("quest/snake_blade", 1);
    call_out("do_fight",10,this_object(),enemy);
    return;
}
void create()
{
    set_name("偷蛇", ({ "thief snake", "snake" }) );
    set_race("human");
    set("gender", "male");
    set_level(33+random(3));
    set("age", 20+random(21));
    set("limbs", ({ "蛇頭", "蛇尾", "腹部", "胸口", "腳部", "肩膀", "腰部" }) );
    set("title",HIG"蛇族襲士"NOR);
    set("long", "手持短刃，身穿黑衣，專門遊走在草叢間。\n");
    set("attitude", "aggressive");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    if( this_object()->query_temp("quest/snake_blade") == 1) {
        set("chat_chance_combat", 7);
        set("chat_msg_combat", ({
            (: command, "peer" :),
        }) );
    } else {
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
            (: command, "peer" :),
            (: do_fight :),
        }) );
    }
    set("set_drop", ({
        ([ "type":"eq", "id":87, "amount":1, "p1":1, "p2":100 ]),     // 蛇神項鍊
        ([ "type":"wp", "id":49, "amount":1, "p1":1, "p2":300 ]),     // 彎刀
        ([ "type":"wp", "id":30, "amount":1, "p1":1, "p2":200 ]),     // 突擊戰刀
        ([ "type":"food", "id":30, "amount":1, "p1":35, "p2":100 ]),  // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":35, "p2":100 ]),   // 蛇皮
        ([ "type":"wp", "id":14, "amount":1, "p1":30, "p2":100 ]),    // 蛇牙
        ([ "type":"obj", "id":82, "amount":1, "p1":20, "p2":100 ]),   // 蛇毒
    }) );
    setup();
}
