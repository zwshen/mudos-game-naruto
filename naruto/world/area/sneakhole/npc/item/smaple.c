#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"蜘蛛標本"NOR, ({ "spider sample", "sample", "__SAMPLE__" }));
    if( !clonep() ) {
        set("base_unit", "盒");
        set("unit", "盒");
        set("base_value", 500);
        set("base_weight", 100);
        set("long", "一盒用劇毒蜘蛛所做的標本。\n");
    }
    setup();
}
