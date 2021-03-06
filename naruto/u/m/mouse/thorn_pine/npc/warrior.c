#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

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
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("$N蹲著馬步，一招『"HIR"崩拳"NOR"』打向$n胸口！\n"NOR, this_object(), enemy);
    damage = 20+random(56);
    if( random(enemy->query_ability("intimidate")) > 100) {
        message_vision("        $n以柔剋剛化解了攻勢。(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        $n「碰！」地一聲退後幾步，嘴角還流出鮮血。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    return;
}
void create()
{
    set_name("豹武者", ({ "bow warrior", "warrior" }));
    set_race("human");
    set_level(35);
    set("gender", "male");
    set("age", 20+random(51));
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "豹族人武者，平常負責打獵、戰鬥與訓練。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 15);
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
