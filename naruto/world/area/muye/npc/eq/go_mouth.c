#include <ansi.h>
#include <armor.h>

inherit F_FACE_EQ;

void create()
{
    set_name(HIY"鳥嘴"NOR, ({ "goose's mouth", "mouth" }) );

    set_weight(800);
    setup_face_eq();

    if( !clonep() ) {
        set("unit", "張");
        set("value", 9050);
        set("long", "把這個戴在嘴上你便擁有一張長長的鳥嘴。\n");
        set("wear_as", "face_eq");
        set("apply_armor/face_eq", ([
            "str": 1,
            "armor": 1,
            "attack": 5,
            "intimidate": 5,
        ]));
    }
    setup();
}
