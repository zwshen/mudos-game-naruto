#include <ansi.h>
#include <armor.h>

inherit F_FACE_EQ;

void create()
{
    set_name(HIK"咒印覆面"NOR, ({ "spells mask", "mask" }) );
    set_weight(1000);
    setup_face_eq();
    if( !clonep() ) {
        set("unit", "件");
        set("value", 142200);
        set("long", "大蛇丸的咒印，覆在臉上能力將大幅提升。\n");
        set("wear_as", "face_eq");
        set("apply_armor/face_eq", ([
            "armor": 5,
            "exact": 15,
            "attack": 10,
            "continual hit": 10,
            "str": 2,
            "con": 2,
        ]));
    }
    setup();
}
