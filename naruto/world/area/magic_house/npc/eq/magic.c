#include <ansi.h>
#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name(MAG"魔"NOR"術"HIM"手"NOR"腕", ({ "magic finesse", "finesse" }) );
    set_weight(500);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 14500);
        set("long", "帶上的人便會感覺手部所受的重量變輕了，魔法般的手鍊。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "evade": 5,
            "wittiness": 3,
            "con": 2,
            "armor": 5,
        ]));
    }
    setup();
}
