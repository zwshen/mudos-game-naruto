#include <ansi.h>
#include <armor.h>
inherit F_FINGER_EQ;

void create()
{
    set_name("新手戒指", ({ "newbie ring","ring" }) );
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 10);
        set("long", "一枚新手戒指，木頭製成的沒什麼防護能力。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "intimidate": 1,
        ]));
    }

    setup();
}


