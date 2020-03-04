#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"Á­½¸Ä²¨¤"NOR, ({ "cockroach's antenna", "antenna" }));
    if( !clonep() ) {
        set("base_unit", "®Ú");
        set("base_value", 4);
        set("base_weight", 100);
        set("long", "¤@¤ä´c¯äªºÁ­½¸Ä²¨¤¡C\n");
    }
    setup();
}