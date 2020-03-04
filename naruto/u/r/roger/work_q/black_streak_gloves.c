#include <ansi.h>
#include <armor.h>
inherit F_HAND_EQ;
inherit ENHANCE_D;

void create()
{
    set_name( "黑閃電手甲", ({ "black streak gloves","gloves" }) );

    set_weight(1500);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "雙");
         set("value", 24000);
        set("long", "這是一雙以不知名的黑色金屬所打造的手甲，質地非常的堅硬。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 8,
        ]));
    }

    setup();
      ENHANCE_D->enhance_armor(this_object(), "hand_eq");
}


