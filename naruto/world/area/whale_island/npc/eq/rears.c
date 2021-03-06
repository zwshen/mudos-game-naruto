#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIW"兔耳朵"NOR, ({ "rabbit's ears", "ears" }) );

    set_weight(3300);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 200);
        set("long", "一對雪白且長長的兔耳朵，會有讓人銷魂的慾望。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
