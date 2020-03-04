#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(HIK"公"NOR, ({ "the king of mouse", "mouse", "king" }) );
    set_race("beast");
    set_level(21);
    set("title", "胊ρ公");
    set("long", "唉偶ぜぜ跑エρ公癬ㄓ籔ρ公ぃ\n");
    set("limbs", ({ "公繷", "ō砰", "浮场", "公籐", "Юぺ" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 笆ю阑
    set("set_drop", ({
        ([ "type":"food", "id":35, "amount":1, "p1":80, "p2":100 ]),   // 公ヘ
        ([ "type":"food", "id":36, "amount":1, "p1":80, "p2":100 ]),   // 公竲
        ([ "type":"food", "id":37, "amount":1, "p1":80, "p2":100 ]),   // 公Ю
        ([ "type":"eq", "id":53, "amount":1, "p1":80, "p2":100 ]),     // 公繷
        ([ "type":"eq", "id":54, "amount":1, "p1":3, "p2":100 ]),      // 忌
    }) );
    setup();
    add_temp("apply/attack", 20);
    set_skill("combat", 110);
    set_skill("dodge", 110);
    set_skill("parry", 110);
    set_skill("savage hit", 110);
    set_skill("heavy hit", 110);
    set_skill("continual hit", 110);
}
