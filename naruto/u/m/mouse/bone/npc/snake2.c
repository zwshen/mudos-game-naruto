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
    int damage, i;
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
    i = random(3);
    if( i == 0 ) {
        message_vision("$N"HIR"拿起木杖隨手一揮，快速打出火彈朝"NOR"$n"HIR"擲來！\n"NOR, this_object(), enemy);
        if( random(this_object()->query_ability("attack")) > random(enemy->query_ability("defend")) ) {
            damage = 90;
        } else {
            damage = 1+random(90);
        }
        if( random(3) > 1) {
            message_vision("        但是火彈打偏了。(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->start_busy(1);
            return;
        }
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        「轟隆」一聲，$n被燒成一位裸體的黑人。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        return;
    } else
    if( i == 1) {
        message_vision("$N"HIC"拿起木杖朝"NOR"$n"HIC"一指！發出兩道冰刺順著木杖方向戳去！\n"NOR, this_object(), enemy);
        if( random(this_object()->query_ability("attack")) > random(enemy->query_ability("defend")) ) {
            damage = 75;
        } else {
            damage = 1+random(75);
        }
        if( random(3) > 1) {
            message_vision("        但是冰刺飛到一半就溶化了。(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->start_busy(1);
            return;
        }
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        「框啷」一聲，冰刺戳的$n直發抖。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        enemy->start_busy(1);
        return;
    }
    message_vision("$N"HIW"拿起木杖揮了幾下，卻沒發生任何事。\n"NOR, this_object(), enemy);
    return;
}
void create()
{
    set_name("巫蛇", ({ "wizard snake", "snake" }) );
    set_race("human");
    set("gender", "female");
    set_level(33+random(3));
    set("age", 20+random(41));
    set("limbs", ({ "蛇頭", "蛇尾", "腹部", "胸口", "腳部", "肩膀", "腰部" }) );
    set("title",HIG"蛇族巫師"NOR);
    set("long", "手持一根木杖的蛇人，頭上帶著一塊布遮住牠的表情。\n");
    set("attitude", "aggressive");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: command, "say 給予蛇族強大的力量！" :),
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"eq", "id":87, "amount":1, "p1":1, "p2":100 ]),     // 蛇神項鍊
        ([ "type":"wp", "id":51, "amount":1, "p1":1, "p2":200 ]),     // 蛇杖
        ([ "type":"food", "id":30, "amount":1, "p1":35, "p2":100 ]),  // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":35, "p2":100 ]),   // 蛇皮
        ([ "type":"wp", "id":14, "amount":1, "p1":30, "p2":100 ]),    // 蛇牙
        ([ "type":"obj", "id":82, "amount":1, "p1":20, "p2":100 ]),   // 蛇毒
    }) );
    setup();
}
