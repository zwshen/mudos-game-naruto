#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(NOR"炎灰"NOR, ({ "ash" }));
    if( !clonep() ) {
        set("base_unit", "團");
        set("unit", "團");
        set("base_value", 2);
        set("base_weight", 1);
        set("long", "因為燒結過長而直接化為粉末的物體，比沙子還要細小。");
    }
    setup();
}