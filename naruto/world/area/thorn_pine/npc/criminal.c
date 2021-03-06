#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void do_fight()
{
    int damage, raiseDamage;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    this_object()->damage_stat("mp", 15, this_object());
    message_vision("\n$N深吸了一口氣將銬著手銬的雙手彎曲，「"HIK"肘擊"NOR"」快速的撞向$n！\n"NOR, this_object(), enemy);

    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("$n立刻伸出左拳蹲了下來，只見$N自己撞向$n的左拳跌在地上。\n\n", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    if( enemy->query("guild") == "piece" ) raiseDamage = 400;
    else raiseDamage = 300;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
    add_temp("apply/attack", -raiseDamage);

    if( damage < 150 ) damage = 100 + random(50);

    enemy->receive_damage(damage, this_object());
    message_vision( sprintf("「碰！」地一聲$n整個被打翻了一圈，頭昏腦漲東南西北都分不清楚(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    return;
}
void create()
{
    set_name("豹人罪犯", ({ "bow criminal", "criminal" }));
    set_race("human");
    set_level(25+random(11));
    set("age", 5+random(81));
    set("camp", "bow");
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "犯了村規的豹人，正在轟天瀑這裡接受處罰。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"wp", "id":45, "amount":1, "p1":20, "p2":100 ]),  // 木劍
        ([ "type":"wp", "id":33, "amount":1, "p1":10, "p2":100 ]),  // 大木棒
        ([ "type":"wp", "id":41, "amount":1, "p1":10, "p2":100 ]),  // 刺木刀
        ([ "type":"wp", "id":39, "amount":1, "p1":1, "p2":100 ]),   // 軟槍
        ([ "type":"wp", "id":36, "amount":1, "p1":1, "p2":150 ]),   // 刻紋劍
    }) );
    setup();
}