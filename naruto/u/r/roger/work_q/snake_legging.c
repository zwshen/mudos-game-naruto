#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name(GRN"青蛇護腿"NOR, ({ "snake legging", "legging" }) );

    set_weight(800);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 6000);
        set("long", "青蛇皮製成的護腿，因韌性十足穿戴起來相當容易活動。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "dex": 1,
            "move": 2,
            "ap": 20,
            "mp": 30,
        ]));
    }

    setup();
}
