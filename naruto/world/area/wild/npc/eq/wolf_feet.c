#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name(YEL"狼腳"NOR, ({ "wolf's afterward feet", "feet" }) );

    set_weight(2000);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 200);
        set("long", "一對狼的後腳，讓你可以裝成狼。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
