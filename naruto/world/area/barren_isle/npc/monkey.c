#include <npc.h>
#include <ansi.h>

void do_fight()
{
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
    if( this_object()->query_leader() != enemy ) {
        this_object()->set_leader(enemy);
        message_vision("$N決定開始跟隨$n一起行動。\n", this_object(), enemy);
    }
}
void create()
{
    set_name("飛天猴", ({ "fly monkey", "monkey" }) );
    set_race("beast");
    set_level(20);
    set("long", "長了翅膀的猴子，身體因為重量輕而細長。\n");
    set("limbs", ({ "猴頭", "身體", "腹部", "猴臂", "翅膀" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊

    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));

    // 戰鬥動作
    set("chat_chance_combat", 80);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    setup();
    add_temp("apply/attack", 20);
}
