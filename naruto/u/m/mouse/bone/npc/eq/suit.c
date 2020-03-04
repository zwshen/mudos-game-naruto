#include <ansi.h>
#include <armor.h>
inherit F_ARMOR;

void create()
{
    set_name(HIG"通大衣"NOR, ({ "ton suit", "suit" }) );
    set_weight(6000);
    setup_armor();
    if( !clonep() ) {
        set("unit", "件");
        set("value", 5200);
        set("long", "通倍利所穿的衣服，看起來厚重保暖。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 10,
            "dex": 1,
            "hp": 70,
        ]));
    }
    setup();
}
