#include <ansi.h>
#include <npc.h>

inherit F_SEASOLDIER;

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
    message_vision("\n$N用手中的鐵刀從狠辣地角度朝$n用力一揮！\n", this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("$n馬上用自己的兵刃架開$N的攻擊。\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    damage = 250;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/righthand"));
    add_temp("apply/attack", -raiseDamage);

    if( damage < 50 ) damage = 20 + random(30);

    // 傷害盾吸收
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("「刷」地一聲，$n被鐵刀砍傷，留下了一道深深的傷口(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    return;
}
void create()
{
    set_name("海軍大尉", ({ "officer" }) );
    set_race("human");
    set_level(32);
    set("title",HIB"本部"NOR);
    set("gender", "male");
    set("class","officer_sea");
    set("camp", "police");
    set("age", 10+random(71));
    set("long", "似乎是這艘船艦的艦長，正專心地看著海圖和路境指揮副手。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "say 看清楚行進方向！" :),
        (: command, "say 左舵三十度！" :),
        (: command, "say 右滿舵！注意前方海流！" :),
        (: command, "say 副官！叫海兵們認真操練，我怎麼聽不到操練的聲音！" :),
    }));
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":1, "p1":40, "p2":100 ]),    // 黃金
        ([ "type":"eq", "id":97, "amount":1, "p1":10, "p2":100 ]),     // 海軍短袖汗衫
        ([ "type":"eq", "id":95, "amount":1, "p1":1, "p2":300 ]),      // 海軍帽
    }) );
    setup();
    carry_object(_DIR_AREA_"thorn_pine/npc/wp/iron_blade.c")->wield();
}