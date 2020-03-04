#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void create()
{
    set_name("癨", ({ "bow child", "child" }));
    set_race("human");
    set_level(25);
    set("age", 5+random(15));
    set("camp", "bow");
    set("limbs", ({ "繷场", "ō砰", "浮场", "籐场", "Юぺ", "φΨ", "场", "璉场" }));
    set("long", "癨タい瑼\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
        (: command, "say " :),
        CYN"癨е贾矪睹禲\n"NOR,
    }));
    set("set_drop", ({
        ([ "type":"wp", "id":45, "amount":1, "p1":10, "p2":100 ]),  // れ糃
        ([ "type":"wp", "id":33, "amount":1, "p1":5, "p2":100 ]),   // れ次
        ([ "type":"wp", "id":41, "amount":1, "p1":5, "p2":100 ]),   // れ
    }) );
    setup();
}
int accept_fight(object ob)
{
    if( this_player()->query_temp("quest/villpk") < 1) {
        do_chat(({
           (: command, "sorry" :),
           (: command, "say 壁Τキぃ非ゴ琜" :),
        }));
        return 0;
    }
    return ::accept_fight(ob);
}
