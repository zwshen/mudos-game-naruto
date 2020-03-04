#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"·ÑÄq"NOR, ({ "coal", "_COAL_" }));
    if( !clonep() ) {
        set("base_unit", "Áû");
        set("unit", "Áû");
        set("base_value", -1);
        set("base_weight", 10);
        set("long", "¶Â¶Âªº·ÑºÒ¡A¾A¦X¥Î¨Ó¿N¤õ¥[·Å¡C");
    }
    setup();
}
