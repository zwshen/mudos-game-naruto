#include <ansi.h>
#include <armor.h>
inherit F_CLOTH;

void create()
{
    set_name(YEL"猴皮"NOR, ({ "monkey leather", "leather" }));
    set_weight(600);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "張");
        set("value", 100);
        set("long", "從猴子身上扯下來的猴皮。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 1,
        ]));
    }
    setup();
}
