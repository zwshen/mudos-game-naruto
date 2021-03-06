#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void do_fight()
{
    object enemy;
    int exact, evade;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if(enemy->is_busy()) {
        message_vision(CYN"$N唱出動人的歌聲。\n"NOR, this_object(), enemy);
        return;
    }
    exact = this_object()->query_level();
    evade = enemy->query_level();

    this_object()->damage_stat("mp", 15, this_object());
    message_vision(CYN"\n$N清了清嗓子，唱著令人動聽的歌聲，令$n心裡小鹿亂撞...\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
        message_vision("$n甩了甩頭讓自己清醒過來，慶幸差點就把持不住。\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    message_vision("$n完全被歌聲所吸引，臉上充滿了白癡的笑容。\n\n", this_object(), enemy);
    enemy->start_busy(3);
    return;
}
void create()
{
    set_name("豹歌手", ({ "bow singer", "singer" }));
    set_race("human");
    set_level(35);
    set("gender", "female");
    set("age", 20+random(51));
    set("camp", "bow");
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "豹族人歌手，平常負責唱歌、跳舞與安撫人心。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        CYN"豹歌手美妙的歌聲讓四周豹人拍手叫好。\n"NOR,
        CYN"豹歌手高聲的唱著歌曲。\n"NOR,
    }));
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"wp", "id":33, "amount":1, "p1":15, "p2":100 ]),  // 大木棒
        ([ "type":"wp", "id":34, "amount":1, "p1":5, "p2":100 ]),   // 鐵刀
        ([ "type":"wp", "id":43, "amount":1, "p1":1, "p2":100 ]),   // 刺木槍
        ([ "type":"wp", "id":36, "amount":1, "p1":1, "p2":150 ]),   // 刻紋劍
    }) );
    setup();
}
int accept_fight(object ob)
{
    if( this_player()->query_temp("quest/villpk") < 1) {
        do_chat(({
           (: command, "sorry" :),
           (: command, "say 族長有令，平時一律不準打架" :),
        }));
        return 0;
    }
    return ::accept_fight(ob);
}