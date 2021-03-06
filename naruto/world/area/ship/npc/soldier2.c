#include <ansi.h>
#include <npc.h>

inherit F_SEASOLDIER;

void create()
{
    set_name("海軍雜役", ({ "worker" }) );
    set_race("human");
    set_level(16);
    set("title",HIB"本部"NOR);
    set("gender", "male");
    set("class","work_sea");
    set("camp", "police");
    set("age", 10+random(71));
    set("long", "新入海軍士兵，不過身為本部人員，雜役也不容忽視。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"eq", "id":97, "amount":1, "p1":1, "p2":200 ]),                 // 海軍短袖汗衫
        ([ "type":"eq", "id":95, "amount":1, "p1":1, "p2":800 ]),                 // 海軍帽
    }) );
    setup();
}
