#include <ansi.h>
#include <armor.h>
inherit F_ARMOR;

void create()
{
    set_name(GRN"竹甲"NOR, ({ "bamboo armor", "armor" }) );

    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 300);
        set("long", "一件竹子製成的鎧甲，好像沒什麼防護的功\能。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 3,
        ]));
    }

    setup();
}

