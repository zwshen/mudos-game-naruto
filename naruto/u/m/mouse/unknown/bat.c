#include <npc.h>

void create()
{
    set_name("娇交", ({ "bat" }) );
    set_race("beast");
    set_level(3);

    set("long", "炊硄娇交狦獻╡盻マ琌穦砆ю阑\n");

    set("limbs", ({ "交繷", "交ō", "交羖", "交φ" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 笆ю阑

    set("set_drop", ({
    //  ([ "type":"eq", "id":??, "amount":1, "p1":10, "p2":100 ]),     // 跨羖
    }) );

    setup();
}
