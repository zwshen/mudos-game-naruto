#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(HIK"跑公"NOR, ({ "the king of mouse", "mouse", "king" }) );
    set_race("beast");
    set_level(70);

    set("title", "Ω跑胊ρ公");
    set("long", "唉偶ぜぜ跑エρ公癬ㄓ籔ρ公ぃ\n");

    set("limbs", ({ "公繷", "ō砰", "浮场", "公籐", "Юぺ" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 笆ю阑

    set("set_drop", ({
        ([ "type":"obj", "id":12, "amount":1, "p1":80, "p2":100 ]),   // 公ヘ
        ([ "type":"obj", "id":13, "amount":1, "p1":80, "p2":100 ]),   // 公竲
        ([ "type":"obj", "id":14, "amount":1, "p1":80, "p2":100 ]),   // 公Ю
        ([ "type":"eq", "id":53, "amount":1, "p1":80, "p2":100 ]),   // 公繷
        ([ "type":"eq", "id":54, "amount":1, "p1":3, "p2":100 ]),   // 忌
    }) );

    setup();

    set_skill("combat", 200);
    set_skill("dodge", 200);
    set_skill("parry", 200);
    set_skill("savage hit", 200);
    set_skill("heavy hit", 200);
    set_skill("continual hit", 200);
    set_temp("apply/attack", 20);
}


