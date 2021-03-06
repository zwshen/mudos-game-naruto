#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name(HIW"無縫內褲"NOR, ({ "under pants", "pants" }) );

    set_weight(1500);
    setup_pants();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long", "一件絲質的內褲，你注意到上面並沒有任何縫痕，穿起來應該會很透氣自在。\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 8,
            "int": 1,
        ]));
    }

    setup();
}

