#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name(HIB"工作褲"NOR, ({ "Work pants", "pants" }) );

    set_weight(1500);
    setup_pants();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10);
        set("long", "材質耐磨，顏色較深就算弄髒了也看不太出來，深受工人喜愛。\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 10,
            "dex": 20,
        ]));
    }

    setup();
}
