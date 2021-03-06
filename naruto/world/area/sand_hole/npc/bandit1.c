#include <npc.h>
#include <ansi.h>
#include "enhance.h"

inherit F_FIGHTER;

void create()
{
    set_name("低級強盜", ({ "bandit" }) );
    set_level(25);
    set_race("human");
    if( random(2) == 1) {
        set("gender", "male");
    } else {
        set("gender", "female");
    }
    set("chat_chance", 20);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("camp", "sand_bandit");
    set("age", 15+random(41));
    set("title",YEL"地下沙穴"NOR);
    set("long", "沒事拿著長刀到處亂逛找人麻煩，一看就知道是最下級的強盜。\n");
    set("item_drop", "/world/area/sand_hole/npc/wp/long_blade.c");
    set("molecule", 1);            // 分子
    set("denominator", 300);       // 分母
    set("set_drop", ({
        ([ "type":"wp", "id":34, "amount":1, "p1":1, "p2":100 ]),                  // 鐵刀
        ([ "type":"obj", "id":29, "amount":10 + random(200), "p1":80, "p2":100 ]), // 銀子
    }) );
    setup();
    carry_object(__DIR__"wp/long_blade.c")->wield("righthand");
    add_temp("apply/armor", 100);
}
