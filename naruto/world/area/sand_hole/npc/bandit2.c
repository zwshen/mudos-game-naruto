#include <npc.h>
#include <ansi.h>
#include "enhance.h"

inherit F_FIGHTER;

void do_fight()
{
    int damage;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("\n$N暴喝一聲，一招"HIC"「單刀直入」"NOR"朝著$n的要害揮出猛力的一刀！\n"NOR,this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("但是$n已經看破了$N的攻勢，拿起武器架住了$N，將攻擊完全停止。\n\n"NOR, this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    this_object()->damage_stat("mp", 25, this_object());
    damage = COMBAT_D->isDamage(this_object(), enemy, this_object()->query_temp("weapon/righthand"));

    if( damage < 150 ) damage = 100 + random(50);
    else damage += 150;

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->receive_damage(damage, this_object());
    message_vision( sprintf("$N將刺進$n要害的長刀拔了出來，鮮血像湧泉般的不停噴出(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    this_object()->start_busy(1);
    return;
}
void create()
{
    set_name("高級強盜", ({ "bandit" }) );
    set_level(35);
    set_race("human");
    if( random(2) == 1) {
        set("gender", "male");
    } else {
        set("gender", "female");
    }
    set("camp", "sand_bandit");
    set("age", 18+random(51));
    set("title",YEL"地下沙穴"NOR);
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("long", "帶著羽毛帽子，手拿著長刀，一臉威武，看起來十分高級的強盜。\n");
    set("item_drop", "/world/area/sand_hole/npc/wp/long_blade.c");
    set("molecule", 1);            // 分子
    set("denominator", 100);       // 分母
    set("set_drop", ({
        ([ "type":"wp", "id":34, "amount":1, "p1":8, "p2":100 ]),                  // 鐵刀
        ([ "type":"obj", "id":29, "amount":10 + random(400), "p1":80, "p2":100 ]), // 銀子
        ([ "type":"eq", "id":27, "amount":1, "p1":20, "p2":100 ]),                 // 羽毛帽
        ([ "type":"eq", "id":15, "amount":1, "p1":6, "p2":100 ]),                  // 白布鞋
    }) );
    setup();
    carry_object("/world/eq/head/plume.c")->wear();
    carry_object(__DIR__"wp/long_blade.c")->wield("righthand");
    add_temp("apply/armor", 150);
    add_temp("apply/attack", 50);
}