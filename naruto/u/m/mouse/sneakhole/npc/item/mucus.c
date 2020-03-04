#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIW"»jµïÂH²G"NOR, ({ "spider mucus", "mucus","_SPIDER_MUCUS_" }));
    if( !clonep() ) {
        set("base_unit", "ªb");
        set("base_value", 60);
        set("base_weight", 100);
        set("long", "¤@¹ÎÂHÂHªº»jµï²GÅé¡C\n");
    }
    setup();
}
