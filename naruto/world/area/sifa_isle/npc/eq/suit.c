#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("海軍西裝上衣", ({ "lounge suit", "suit" }) );

    set_weight(1200);

    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 7500);
        set("long", "海軍的標準服裝，由身份較高的海軍人員所穿著。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 15,
        ]));
    }
    setup();
}
