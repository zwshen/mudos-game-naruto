#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name(HIB"吊帶褲"NOR, ({ "galluses" }) );

    set_weight(800);
    setup_pants();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 8900);
        set("long", "便於活動的長褲，人猿最愛穿的褲子。\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 5,
            "dex": 2,
            "exact": 5,
            "evade": 5,
        ]));
    }
    setup();
}
