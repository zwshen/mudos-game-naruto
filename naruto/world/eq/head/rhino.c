#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIK"犀牛帽"NOR, ({ "rhino hat", "hat" }) );

    set_weight(3000);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 3000);
        set("long", "一頂犀牛造型的帽子，讓你活力充沛。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 6,
        ]));
    }

    setup();
}
