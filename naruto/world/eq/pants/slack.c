#include <ansi.h>
#include <armor.h>

inherit F_PANTS;

void create()
{
    set_name("長褲", ({ "slack" }) );

    set_weight(1500);
    setup_pants();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 200);
        set("long", "一件很普通的長褲。\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "armor": 2,
        ]));
    }

    setup();
}
