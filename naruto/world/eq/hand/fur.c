#include <ansi.h>
#include <armor.h>
inherit F_HAND_EQ;

void create()
{
    set_name(YEL"皮製手套"NOR, ({ "fur gloves","gloves" }) );

    set_weight(1000);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 200);
        set("long", "一雙皮製的手套，戴起來很保暖。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
