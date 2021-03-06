#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void do_fight()
{
    int damage, raiseDamage, exact, evade;
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
    exact = COMBAT_D->intimidate(this_object(), 1)*1.1;
    evade = COMBAT_D->wittiness(enemy, 1);

    this_object()->damage_stat("mp", 20, this_object());
    message_vision("\n$N"HIY"發出汪汪叫聲，只見地面的泥土似乎受到共鳴而漸漸飛起！\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("$n似乎沒有要攻擊的意思，只見泥土又漸漸落了回去。\n\n"NOR, enemy, this_object());
        this_object()->start_busy(2);
    } else {
        raiseDamage = 600;

        add_temp("apply/attack", raiseDamage); 
        damage = COMBAT_D->isDamage(this_object(), enemy, 0);
        add_temp("apply/attack", -raiseDamage);

        if( damage < 200 ) damage = 100 + random(100);

        enemy->receive_damage(damage, this_object());
        message_vision( sprintf("$N所控制的泥塊，瞬間霹靂啪啦地打擊在$n身上，難過至極(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
        this_object()->start_busy(2);
    }
    return;
}
void create()
{
    set_name("狸力", ({ "god monster pig", "pig" }));
    set_level(50);
    set_race("beast");
    set("limbs", ({ "豬頭", "豬尾", "豬豚", "豬耳", "豬腳", "豬肚" }) );
    set("long", "豬狀獸，腳後有突起，聲音就像狗叫。應該是有操土之能。\n");

    set("nickname",HIM"豬狀獸"NOR);
    set("set_drop", ({

    }) );
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":58, "amount":1, "p1":5, "p2":100 ]),     // 精神急救
        ([ "type":"obj", "id":65, "amount":1, "p1":5, "p2":100 ]),     // 體力急救
        ([ "type":"obj", "id":66, "amount":1, "p1":5, "p2":100 ]),     // 念查急救
    }) );
    setup();
}