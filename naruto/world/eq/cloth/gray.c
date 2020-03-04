#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name(HIK"灰色勁裝"NOR, ({ "gray cloth", "cloth" }) );

    set_weight(1200);

    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 800);
        set("long", "一件灰黑的衣服，看你看起來很神秘的感覺。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 8,
        ]));
    }
    setup();
}

