#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("皮帶", ({ "leather belt", "belt" }) );
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 200);
        set("long", "一條繫在腰上讓褲子不會掉的皮帶。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
