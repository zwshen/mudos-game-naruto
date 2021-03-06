#include <npc.h>
#include <ansi.h>

void create()
{
    set_name( HIK"大型毒蛛" NOR, ({ "big spider", "spider" }) );
    set_race("beast");
    set_level(15);

    set("long", "一隻大型的劇毒蜘蛛，比你的手掌張開還要大，長的非常噁心，讓人看了只想作嘔。\n");
    set("title","陰影巢穴");

    set("limbs", ({ "蛛頭", "身體", "腹部", "蛛腿" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 主動攻擊
    set("set_drop", ({
        ([ "type":"obj", "id":52, "amount":1, "p1":80, "p2":100 ]),   // 蜘蛛腿
        ([ "type":"obj", "id":53, "amount":1, "p1":50, "p2":100 ]),   // 蜘蛛眼睛
        ([ "type":"wp", "id":24, "amount":1, "p1":1, "p2":200 ]),     // 大蜘蛛腿
    }) );
    setup();
    add_temp("apply/attack", 20);
}
