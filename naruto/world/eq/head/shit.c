#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(YEL"大便帽"NOR, ({ "shit hat", "hat" }) );

    set_weight(3000);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 700);
        set("long", "一頂大便造型的帽子，似乎是用來搞笑用的。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "int": 1,
        ]));
    }

    setup();
}
