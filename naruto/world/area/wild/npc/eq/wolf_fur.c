#include <armor.h>
#include <ansi.h>

inherit F_CLOTH;

void create()
{
    set_name(YEL"狼皮"NOR, ({ "wolf's fur", "fur" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "張");
        set("value", 300);
        set("long", "一張華麗的狼皮。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }

    setup();
}