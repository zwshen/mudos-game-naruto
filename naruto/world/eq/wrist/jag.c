#include <ansi.h>
#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name("尖刺護腕", ({ "jag wrist", "wrist" }) );
    set_weight(100);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "個");
        set("value", 200);
        set("long", "一個上頭有一圈尖刺的護腕，小心被刺到。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
