#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name(HIY"太陽之護帶"NOR, ({ "sun waist", "waist" }) );
    set_weight(5000);
    setup_waist_eq();
    if( !clonep() ) {
        set("unit", "條");
        set("value", 227500);
        set("no_box", 1);
        set("long", "黃金石像巨兵的護帶，護帶就算在黑暗的地方也能發出光芒。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 10,
            "str": 5,
            "con": 5,
            "dex": 5,
            "int": 5,
        ]));
    }
    setup();
}
