#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIW"羽毛帽"NOR, ({ "plume hat", "hat" }) );

    set_weight(500);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 200);
        set("long", "一頂不知用什麼毛做成得羽毛帽，相當好看。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
