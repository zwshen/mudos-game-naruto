#include <ansi.h>
#include <npc.h>

inherit F_SEASOLDIER;

void do_fight()
{
    int damage, raiseDamage;
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
    message_vision("\n$N半蹲著拿起"HIW"鐵砲"NOR"瞄準$n，「碰」地一聲射出子彈。\n", this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("但是子彈射偏了，沒打中$n。\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    raiseDamage = 50;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/twohanded"));
    add_temp("apply/attack", -raiseDamage);

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("$n被鐵彈擊中了，好像受到了一些傷害(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    return;
}
void create()
{
    set_name("海軍少尉", ({ "officer" }) );
    set_race("human");
    set_level(27);
    set("title",HIB"本部"NOR);
    set("gender", "male");
    set("class","officer_sea");
    set("camp", "police");
    set("age", 10+random(71));
    set("long", "似乎是這艘船艦的副手，不停地指揮著士兵們行動。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":10+random(121), "p1":40, "p2":100 ]),  // 銀子
        ([ "type":"obj", "id":100, "amount":1, "p1":20, "p2":100 ]),              // 彈夾
        ([ "type":"wp", "id":56, "amount":1, "p1":1, "p2":100 ]),                 // 海軍制式鐵砲
        ([ "type":"eq", "id":97, "amount":1, "p1":2, "p2":100 ]),                 // 海軍短袖汗衫
        ([ "type":"eq", "id":95, "amount":1, "p1":1, "p2":450 ]),                 // 海軍帽
    }) );
    setup();
    carry_object(_DIR_AREA_"sifa_isle/npc/wp/gun.c")->wield("twohanded");
}