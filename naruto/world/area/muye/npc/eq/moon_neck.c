#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name(HIY"彎月"NOR"項鍊", ({ "moon necklace", "necklace" }) );
    set_weight(600);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 5200);
        set("long", "一串彎月造型的項鍊，有著神秘的力量。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "int": 4,
        ]));
    }

    setup();
}