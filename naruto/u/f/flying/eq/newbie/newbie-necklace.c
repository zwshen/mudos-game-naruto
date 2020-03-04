#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("新手項鍊", ({ "newbie necklace", "necklace" }) );
    set_weight(300);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 10);
        set("long", "用細鐵絲繞成圈掛在脖子上。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 1,
        ]));
    }

    setup();
}


