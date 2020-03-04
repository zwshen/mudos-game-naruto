#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name("±ú¦Ð", ({ "owl plume", "plume", "_OWL_PLUME_" }));
    if( !clonep() ) {
        set("base_unit", "®Ú");
        set("base_value", 1000);
        set("base_weight", 50);
        set("long", "»a¤§±úªº¦Ð¤ò¡A¤ñ¤@¯ë¦Ð¤ò§ó¥[¬X¶¶¡C\n");
    }
    setup();
}
