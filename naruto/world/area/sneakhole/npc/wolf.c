#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIK"餓狼蜘蛛"NOR, ({ "wolf spider", "spider", "wolf" }) );
    set_race("beast");
    set("title","陰影蜘蛛");
    set_level(26);
    set("long", "突變的大蜘蛛，頭是一隻正流著口水的狼頭，身體卻是八隻腳的蜘蛛。\n");
    set("limbs", ({ "狼頭", "身體", "腹部", "蛛腿" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":52, "amount":2, "p1":80, "p2":100 ]),       // 蜘蛛腿
        ([ "type":"obj", "id":81, "amount":1, "p1":1, "p2":200 ]),        // 蜘蛛標本
        ([ "type":"obj", "id":80, "amount":1, "p1":1, "p2":100 ]),        // 黏液
        ([ "type":"obj", "id":55, "amount":1, "p1":1, "p2":150 ]),        // 蜘蛛胃袋
        ([ "type":"food", "id":19, "amount":1, "p1":5, "p2":100 ]),       // 查克拉丸
        ([ "type":"eq", "id":81, "amount":1, "p1":1, "p2":450 ]),         // 無縫內褲
        ([ "type":"food", "id":17, "amount":1, "p1":5, "p2":100 ]),       // 體力丸
    }) );
    setup();
    add_temp("apply/attack", 30);
    set_skill("combat", 125);
    set_skill("dodge", 125);
    set_skill("parry", 125);
    set_skill("savage hit", 125);
    set_skill("heavy hit", 125);
    set_skill("continual hit", 125);
}
