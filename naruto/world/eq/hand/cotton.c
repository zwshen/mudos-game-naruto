#include <ansi.h>
#include <armor.h>
inherit F_HAND_EQ;

void create()
{
    set_name("布手套", ({ "cotton gloves","gloves" }) );

    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 100);
        set("long", "一個很普通的手套，看起來沒什麼特別之處。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 1,
        ]));
    }

    setup();
}
