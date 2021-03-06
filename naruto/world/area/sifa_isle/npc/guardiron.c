#include <ansi.h>
#include <npc.h>

inherit F_SEASOLDIER;

void do_fight()
{
    int damage, raiseDamage;
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
    message_vision(CYN"\n$N將鐵鍊快速的甩動...只見鐵球被拖向空中...\n"NOR, this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("$N用力朝$n一甩鐵鍊，只見鐵球飛去，在地上砸出一個大洞\n\n", this_object(), enemy);
        this_object()->start_busy(3);
        return;
    }
    raiseDamage = 200;
    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/twohanded"));
    add_temp("apply/attack", -raiseDamage);

    if( damage < 100 ) damage = 50 + random(50);

    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("$N用力朝$n一甩鐵鍊，只見鐵球飛去，正中$n胸口(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    this_object()->start_busy(1);
    return;
}
void create()
{
    set_name("守衛", ({ "guard" }) );
    set_race("human");
    set_level(30);
    set("title",HIC"司法島"NOR);
    set("nickname",HIK"鐵球部隊"NOR);
    set("class", "guard_sea");
    set("camp", "police");
    set("age", 10+random(71));
    set("long", "身材壯碩的士兵，手上的鐵鍊拖著一顆比人還大的鐵球。\n");
    set("chat_chance", 15);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":100, "amount":1, "p1":60, "p2":100 ]),              // 彈夾
        ([ "type":"obj", "id":102, "amount":1, "p1":40, "p2":100 ]),              // 火繩
        ([ "type":"wp", "id":61, "amount":1, "p1":1, "p2":400 ]),                 // 鐵球鎖鍊
        ([ "type":"wp", "id":60, "amount":1, "p1":50, "p2":100 ]),                // 鐵球
    }) );
    setup();
    carry_object(__DIR__"wp/ball.c")->wield("twohanded");
}