#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name(RED"惡鬼靴"NOR, ({ "ghost boots", "boots" }) );

    set_weight(1500);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 8500);
        set("long", "透著一股邪氣的靴子，穿久了也許會招來惡運。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
        	"armor": 3,
            "evade": 5,
            "wittiness": 5,
        ]));
    }

    setup();
}