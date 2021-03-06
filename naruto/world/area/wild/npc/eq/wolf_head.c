#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(YEL"狼頭"NOR, ({ "wolf's head", "head" }) );

    set_weight(1000);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 200);
        set("long", "一對狼造型的頭，可以假扮成狼。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
