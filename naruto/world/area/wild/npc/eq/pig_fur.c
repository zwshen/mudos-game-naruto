#include <armor.h>
#include <ansi.h>

inherit F_CLOTH;

void create()
{
    set_name(HIK"¶Â½Þ¥Ö"NOR, ({ "pig's fur", "fur" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "±i");
        set("value", 200);
        set("long", "¤@±iÂK¶Â²ÊÁWªº¶Â½Þ¥Ö¡C\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }

    setup();
}