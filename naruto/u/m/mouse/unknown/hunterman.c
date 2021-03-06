#include <npc.h>
#include <ansi.h>

inherit F_BANDIT;

void create()
{
    set_name("獵人先生", ({ "hunter man", "man" }) );
    set_race("human");
    set_level(20);
    set("long", "在森林中抓了一隻幼狐熊的壞人，自稱職業獵人。\n");
    set("age", 50);
    set("gender", "male");
    set("chat_chance", 5);
    set("chat_msg", ({
       (: command, "say 我可是職業獵人喔。" :),
       (: command, "say 幼狐熊算什麼！有空在去抓隻大的來給大家觀賞！" :),
    }) );
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
         (: command, "say 這傢伙想放走狐熊阿！":),
         (: command, "say 我可是職業獵人！":),
         (: command, "say 你還敢打我嗎？！" :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":61+random(40), "p1":60, "p2":100 ]),  // 銀子
        ([ "type":"wp", "id":11, "amount":1, "p1":5, "p2":100 ]),     // 短劍
    //  ([ "type":"obj", "id":??, "amount":1, "p1":20, "p2":100 ]),   // 捕獸夾
    //  ([ "type":"wp", "id":??, "amount":1, "p1":10, "p2":100 ]),    // 來福槍
    }) );
    setup();
}
void init()
{
    if( this_player()->id("_HELP_BEAR_") && !this_player()->is_fighting(this_player()) ) {
        message_vision(HIR"$N一見到$n便大聲叫著：「居然被放出來了！別想跑！」\n\n"NOR, this_object(), this_player());
        this_object()->kill_ob(this_player());
    }
}
