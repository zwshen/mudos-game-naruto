#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIK"公繷"NOR, ({ "mouse's head", "head" }) );

    set_weight(1000);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "聋");
        set("value", 100);
        set("long", "癸ρ公硑繷安шΘρ公");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 1,
        ]));
    }

    setup();
}
