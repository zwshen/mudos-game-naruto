#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIW"®Û¶ê°®"NOR, ({ "Longan", "longan" }));
    if( !clonep() ) {
        set("base_unit", "³U");
        set("base_value", -1);
        set("unit", "³U");
        set("base_weight", 500);
        set("long", "°ó¬î©ÒÃØ°eªº¤@³U®Û¶ê°®¡A¤S³QºÙ¬°Às²´¡C\n");
    }
    setup();
}
