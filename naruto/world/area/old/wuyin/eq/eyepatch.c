#include <ansi.h>
#include <armor.h>

inherit F_FACE_EQ;

void create()
{
    set_name(HIK"黑色眼罩"NOR, ({ "eyepatch" }) );

    set_weight(1500);

    setup_face_eq();

    if( !clonep() ) {
        set("unit", "隻");
        set("value", 8000);
        set("long", "一隻單眼眼罩，用來耍帥用的。\n");
        set("wear_as", "face_eq");
        set("apply_armor/face_eq", ([
            "wittiness": 1,
            "armor": 1,
        ]));
    }

    setup();
}
