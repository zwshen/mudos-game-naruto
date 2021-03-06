#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void create()
{
    set_name("豹人", ({ "bow man", "man" }));
    set_race("human");
    set_level(30);
    set("gender", "male");
    set("age", 10+random(81));
    set("limbs", ({ "頭部", "身體", "腹部", "腿部", "尾巴", "耳朵", "肩部", "背部" }));
    set("long", "豹村的豹族人，正愉快的生活著。\n");
    set("camp", "bow");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
        (: command, "say 歡迎來到豹族的村子" :),
        CYN"豹人高興的哼著歌曲。\n"NOR,
    }));
    	
    set("set_drop", ({
      ([ "type":"wp", "id":45, "amount":1, "p1":20, "p2":100 ]),  // 木劍
      ([ "type":"wp", "id":35, "amount":1, "p1":10, "p2":100 ]),  // 鐵勾
      ([ "type":"wp", "id":44, "amount":1, "p1":5, "p2":100 ]),   // 迴旋斧
      ([ "type":"wp", "id":43, "amount":1, "p1":1, "p2":100 ]),   // 刺木棒
    }));

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
