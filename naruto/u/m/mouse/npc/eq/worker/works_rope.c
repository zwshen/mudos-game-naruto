#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name(HIW"安全繩索"NOR, ({ "Safe rope", "rope" }) );
    set_weight(2000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 10);
        set("long", "工地的必備道具，以防墜落意外的發生。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 10,
            "con": 20,
            "savage hit": 20,
        ]));
    }

    setup();
}
