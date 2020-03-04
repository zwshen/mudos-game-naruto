#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIW"ÃT³½¥Ö"NOR, ({ "sharkskin" }));

    if( !clonep() ) {
        set("base_unit", "±i");
        set("base_value", 200);
        set("base_weight", 1000);
        set("long", "ÃT³½ªº¥~¥Ö¡A¦ü¥GÆZ°íµwªº¡C\n");
    }
    setup();
}
