#include <ansi.h>
#include <armor.h>
inherit F_HAND_EQ;

void create()
{
    set_name("����M", ({ "cotton gloves","gloves" }) );

    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "��");
        set("value", 100);
        set("long", "�@�ӫܴ��q����M�A�ݰ_�ӨS����S�O���B�C\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 1,
        ]));
    }

    setup();
}