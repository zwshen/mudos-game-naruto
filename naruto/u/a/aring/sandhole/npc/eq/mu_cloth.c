#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name(YEL"肌肉衣"NOR, ({ "scorpin musclebig cloth", "cloth" }) );

    set_weight(1200);

    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 28000);
        set("long", "穿上肌肉會變很大的衣服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 12,
            "con": 5,
            "hp": 50,
            "intimidate": 10,
                    ]));
    }
    setup();
}

