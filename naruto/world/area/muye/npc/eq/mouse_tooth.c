/* mouse_tooth.c
   木葉村下水道鼠王特別防具...
   write by -Acme-
*/

#include <ansi.h>
#include <armor.h>

inherit F_FACE_EQ;

void create()
{
    set_name(HIK"大暴牙"NOR, ({ "mouse's tooth", "tooth" }) );

    set_weight(800);
    setup_face_eq();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 101900);
        set("long", "把這個戴在嘴上你便擁有一對大暴牙。\n");
        set("wear_as", "face_eq");
        set("apply_armor/face_eq", ([
            "armor": 2,
            "exact": 10,
            "intimidate": 10,
            "continual hit": 10,
            "str": 3,
        ]));
    }
    setup();
}
