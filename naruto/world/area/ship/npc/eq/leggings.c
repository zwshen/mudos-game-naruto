#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name(YEL"·áµU"HIW"Å@»L"NOR, ({ "pongo leggings", "leggings" }) );

    set_weight(2000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "Âù");
        set("value", 22000);
        set("long", "¤H·á©Ò¬ïªºÅ@»L¡A¤òµ³µ³ªº¦ü¥GÁÙ«Ü«O·x¡C\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 10,
            "evade": 10,
        ]));
    }
    setup();
}
