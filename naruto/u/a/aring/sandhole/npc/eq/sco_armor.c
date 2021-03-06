#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name(NOR+MAG"蠍殼甲"NOR, ({ "scorpion armor", "armor" }) );
    set_weight(730);
    setup_armor();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 500);
        set("long", "蠍子外殼形成的堅硬護甲，但重量想像中輕巧很多。\n");
        set("wear_as", "armor");
        set("apply_armor/armor_eq", ([
            "dex": 1,
            "con": -1,
            "dodge": 2,
            "armor": 4,
        ]));
    }

    setup();
}

