#include <npc.h>
#include <ansi.h>
#include "sand_sk.h"

void create()
{
    set_name("沼澤怪", ({ "fen" }) );
    set_level(35);
    set_race("human");
    if( random(2) == 1) set("gender", "male");
    else set("gender", "female");
    set("limbs", ({ "爛泥", "觸手", "眼睛", "嘴巴", "黏液" }) );
    set("age", 15+random(80));
    set("long", "爛啪啪的就像一團汙泥，只是多了兩顆眼睛一張嘴。\n");
    set("attitude", "aggressive");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 35);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":151, "amount":random(20)+1, "p1":80, "p2":100 ]),  // 廢土
        ([ "type":"obj", "id":152, "amount":random(10)+1, "p1":80, "p2":100 ]),  // 塵埃
        ([ "type":"obj", "id":153, "amount":random(3)+1, "p1":80, "p2":100 ]),   // 爛果
        ([ "type":"obj", "id":156, "amount":random(5)+1, "p1":80, "p2":100 ]),   // 碎石
        ([ "type":"obj", "id":154, "amount":random(5)+1, "p1":30, "p2":100 ]),   // 沙礫
        ([ "type":"obj", "id":149, "amount":random(2)+1, "p1":10, "p2":100 ]),   // 結塊
    }) );
    setup();
    add_temp("apply/armor", 50);
}

void die()
{
    object enemy, killer;
    int i;
    enemy = this_object()->last_damage_giver();

    if( !enemy ) {
        ::die();
        return;
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    i = query_level()*5 - random(query_level());

    if( killer->query_level() - 10 <= this_object()->query_level() && killer->query_point("learn") < 3000000 ) {
        tell_object(killer, HIR"\n你殺死了"+this_object()->query("name")+"而額外獲得了 "HIY+i+HIR" 點學點。\n"NOR);
        killer->add_point("learn", i);
    }
    ::die();
    return;
}