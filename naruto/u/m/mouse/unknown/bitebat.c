#include <npc.h>

void create()
{
    set_name("﹀娇交", ({ "bite bat", "bat" }) );
    set_race("beast");
    set_level(6);

    set("long", "ゑ耕唉娇交キ盽尺舧﹀睪\n");

    set("limbs", ({ "交繷", "交ō", "交羖", "交φ" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 笆ю阑

    set("set_drop", ({
    //  ([ "type":"eq", "id":??, "amount":1, "p1":20, "p2":100 ]),     // 跨羖
    }) );

    setup();
}
