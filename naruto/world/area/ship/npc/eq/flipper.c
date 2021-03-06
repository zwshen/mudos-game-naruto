#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name(GRN"蛙鞋"NOR, ({ "flipper" }) );

    set_weight(1000);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 31500);
        set("long", "像青蛙腳掌一般的鞋子，能在海中快速游動。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 5,
            "evade": 12,
        ]));
    }
    setup();
}
