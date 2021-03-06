#include <ansi.h>
#include <npc.h>

inherit F_SEABANDIT;

void do_fight()
{
    int damage, raiseDamage, exact, evade;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    exact = COMBAT_D->exact(this_object(), enemy, 1);
    evade = COMBAT_D->wittiness(enemy, 1);

    message_vision("\n$N用火砲對準$n，轟隆一聲發射出去，$N整個人跌了一跤。\n", this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("結果火砲打中了地面，地上一片焦黑。\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    raiseDamage = 150;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/twohanded"));
    add_temp("apply/attack", -raiseDamage);

    if( damage < 50 ) damage = 40 + random(10);

    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("$n「磅」地一聲，火彈在$n的身上炸開，受到嚴重的傷害(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    return;
}
void create()
{
    set_name("砲擊手", ({ "shelling man", "man" }) );
    set_race("human");
    set_level(30);
    set("title",HIY"猿山連合"NOR);
    set("gender", "male");
    set("class","little_sea");
    set("camp", "robber");
    set("age", 10+random(71));
    set("long", "身上背著從海軍搶來的槍支，似乎對火炮操縱十分拿手。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "say 這片海域是屬於我們猿山連合軍的" :),
    }));
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":102, "amount":1, "p1":30, "p2":100 ]),      // 火繩
        ([ "type":"wp", "id":58, "amount":1, "p1":1, "p2":200 ]),         // 海軍制式火炮
        ([ "type":"obj", "id":100, "amount":1, "p1":30, "p2":100 ]),      // 彈夾
        ([ "type":"wp", "id":56, "amount":1, "p1":1, "p2":100 ]),         // 海軍制式鐵砲
        ([ "type":"eq", "id":100, "amount":1, "p1":1, "p2":200 ]),        // 潛水衣
    }) );
    setup();
    carry_object(_DIR_AREA_"sifa_isle/npc/wp/fire.c")->wield("twohanded");
}