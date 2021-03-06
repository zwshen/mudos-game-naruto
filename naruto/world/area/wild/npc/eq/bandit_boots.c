#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("盜道鞋", ({ "bandit boots", "boots" }) );

    set_weight(3000);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 3400);
        set("long", "一雙穿著可以讓你走路無聲無息。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 4,
            "dex" : 1,
            "int" : 1,
        ]));
    }

    setup();
}
