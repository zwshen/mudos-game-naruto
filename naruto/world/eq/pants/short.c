#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name(HIR"熱褲"NOR, ({ "hot short", "short" }) );
    set_weight(800);
    setup_pants();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 100);
        set("long", "一件超短的熱褲，看起來相當有活力。\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 1,
        ]));
    }

    setup();
}
