#include <npc.h>

void create()
{
    set_name("小狼", ({ "small wolf", "wolf" }) );
    set_race("beast");
    set_level(5);

    set("long", "一隻已經長得和成狼差不多大的小狼。\n");

    set("limbs", ({ "狼頭", "身體", "腹部", "狼腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 主動攻擊

    set("set_drop", ({
        ([ "type":"food", "id":32, "amount":1, "p1":80, "p2":100 ]),   // 狼心
        ([ "type":"food", "id":33, "amount":1, "p1":80, "p2":100 ]),   // 狼肺
        ([ "type":"eq", "id":57, "amount":1, "p1":10, "p2":100 ]),   // 狼腳
        ([ "type":"eq", "id":58, "amount":1, "p1":8, "p2":100 ]),   // 狼皮
        ([ "type":"eq", "id":59, "amount":1, "p1":10, "p2":100 ]),   // 狼腳
        ([ "type":"eq", "id":60, "amount":1, "p1":10, "p2":100 ]),   // 狼頭
        ([ "type":"eq", "id":61, "amount":1, "p1":15, "p2":100 ]),  // 狼尾
    }) );

    setup();
}
