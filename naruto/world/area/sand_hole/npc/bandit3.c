#include <npc.h>
#include <ansi.h>
#include "enhance.h"

inherit F_FIGHTER;

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
    message_vision("\n$N右手長刀搭配左手單刀同時進攻「"HIY"雙刀亂斬"NOR"」一連砍出八八六十四刀！\n"NOR,this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("但是$n已經看破了$N的攻勢，拿起武器架住了$N，將攻擊完全停止。\n\n"NOR, this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    damage = COMBAT_D->isDamage(this_object(), enemy, this_object()->query_temp("weapon/righthand"));

    if( damage < 150 ) damage = 100 + random(50);
    else damage += 150;

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("只見$N右手長刀虛實不分，搭配左手單刀不斷給予$n大大小小的傷口(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);

    damage = COMBAT_D->isDamage(this_object(), enemy, this_object()->query_temp("weapon/lefthand"));

    if( damage < 100 ) damage = 50 + random(25);
    else damage += 75;

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->damage_stat("hp", damage/2, this_object());
    message_vision( sprintf("只見$N左手單刀攻勢猛烈，搭配右手長刀不斷給予$n大大小小的傷口(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    this_object()->start_busy(1);
    return;
}
void create()
{
    set_name("究級強盜", ({ "bandit" }) );
    set_level(40);
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
    set("long", "帶著犀牛帽子，手拿雙刀，名為究極的強盜。不過還是強盜。\n");
    set("item_drop", "/world/area/sand_hole/npc/wp/long_blade.c");
    set("molecule", 5);            // 分子
    set("denominator", 100);       // 分母
    set("set_drop", ({
        ([ "type":"wp", "id":34, "amount":1, "p1":10, "p2":100 ]),                 // 鐵刀
        ([ "type":"wp", "id":52, "amount":1, "p1":1, "p2":300 ]),                  // 破碎刃
        ([ "type":"obj", "id":29, "amount":10 + random(400), "p1":80, "p2":100 ]), // 銀子
        ([ "type":"eq", "id":31, "amount":1, "p1":20, "p2":100 ]),                 // 犀牛帽
        ([ "type":"eq", "id":15, "amount":1, "p1":15, "p2":100 ]),                 // 白布鞋
    }) );
    setup();
    carry_object("/world/eq/head/rhino.c")->wear();
    carry_object(__DIR__"wp/long_blade.c")->wield("righthand");
    carry_object("/world/wp/blade.c")->wield("lefthand");
    add_temp("apply/armor", 200);
    add_temp("apply/attack", 50);
}