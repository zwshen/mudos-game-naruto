#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name(HIW"¨ß§À¤Ú"NOR, ({ "rabbit tail", "tail" }) );

    set_weight(1000);
    setup_pants();

    if( !clonep() ) {
        set("unit", "¥ó");
        set("value", 1200);
        set("long", "¤@Áû³·¥Õ¶êºuºuªº¨ß§À¤Ú¡C");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 5,
            "dex": 1,
        ]));
    }

    setup();
}

