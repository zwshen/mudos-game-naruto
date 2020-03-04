#include <ansi.h>
#include <armor.h>
inherit F_PANTS;

void create()
{
        set_name(HIK"灰色短褲"NOR, ({ "gray short","short" }) );
        set_weight(3000);
        setup_pants();

        if( !clonep() ) {
                set("unit", "件");
                set("value", 10);
                set("long",
                        "一件深灰色的短褲，像是特有的動物所做的毛皮編製品。\n");
                set("wear_as", "pants");
                set("apply_armor/pants", ([
                        "armor" :3,
                ]));
        }

        setup();
}
