#include <ansi.h>
#include <armor.h>
inherit F_WAIST_EQ;
void create()
{
    set_name(HIY"黃金腰帶"NOR, ({ "Gold waist", "waist" }) );
    set_weight(1500);
    setup_waist_eq();
    if( !clonep() ) {
        set("unit", "條");
        set("value", 20);
        set("long", "純金打造的腰帶非常的值錢\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 50,
            "str"  : 5,
            "con"  : 5,
            "dex"  : 5,
            "int"  : 5,
       ]));
    }
    setup();
}
