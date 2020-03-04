#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name(BRED+HIW"¨V¶Â√»∏}"NOR, ({ "bloody leg","leg" }) );

    set_weight(1670);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "≠”");
        set("value", 19500);
        set("long", "¥≥¥≥¶Â¨ı¶Â∏Ò¨V¶b√»∏}§W°C\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "con": 2,
            "str": 2,
            "dex": -2,
            "int": -2,
            "combat" : 10,
        ]));
    }

    setup();
}


