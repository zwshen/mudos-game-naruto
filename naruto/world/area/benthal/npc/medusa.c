#include <npc.h>
#include <ansi.h>

void do_fight()
{
    int exact, evade;
    object enemy;
    mapping cnd = ([]);

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( enemy->query_condition("firelotus", 1) != 0) return;

    message_vision("\n$N觸手翻轉「轟隆」一聲放出一團"HIM"紫色的火燄"NOR"！\n"NOR, this_object(), enemy);

    exact = COMBAT_D->exact(this_object(), enemy, 1);
    evade = COMBAT_D->exact(enemy, this_object(), 1);

    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("紫燄在水中發出「砰」地一聲，變成細小菌絲被水流衝走了。\n\n", enemy, this_object());
        this_object()->start_busy(2);
        return;
    }
    message_vision("紫燄「磅磅磅」地打在$N身上噴出蓮花般的火花，$n看的手舞足蹈。\n\n", enemy, this_object());
    enemy->start_busy(1);
    this_object()->start_busy(1);

    cnd["name"] = HIM+"紫燄"+NOR;
    cnd["duration"] = 3;
    cnd["from"] = this_object();

    enemy->set_condition("firelotus", cnd);
    return;
}

void create()
{
    set_name(HIR"紅燄水母"NOR, ({ "medusa" }) );
    set_level(25);
    set_race("beast");
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");
    set("age", 100+random(200));
    set("limbs", ({ "觸手", "觸鬚", "頭部", "海蜇皮", "軟足" }) );
    set("long", "全身發紅的水母，身在水中感覺非常特別。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 80);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
       ([ "type":"food", "id":65, "amount":1, "p1":1, "p2":10 ]),       // 蚌殼
       ([ "type":"food", "id":74, "amount":1, "p1":1, "p2":15 ]),       // 海膽
       ([ "type":"food", "id":66, "amount":1, "p1":1, "p2":20 ]),       // 烏賊
    }) );
    setup();
}
