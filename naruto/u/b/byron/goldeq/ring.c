#include <ansi.h>
#include <armor.h>
inherit F_FINGER_EQ;
void create()
{
    set_name(HIY"黃金戒子"NOR, ({ "Gold ring", "ring" }) );
    set_weight(1500);
    setup_finger_eq();
    if( !clonep() ) {
        set("unit", "只");
        set("value", 20);
        set("long", "純金打造的戒子非常的值錢\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 50,
            "str"  : 5,
            "con"  : 5,
            "dex"  : 5,
            "int"  : 5,
       ]));
    }
    setup();
}

