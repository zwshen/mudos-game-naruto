#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"樹枝"NOR, ({ "branch", "_BRANCH_" }));
    if( !clonep() ) {
        set("base_unit", "根");
        set("unit", "根");
        set("base_value", 100);
        set("base_weight", 10);
        set("no_box", 1);
        set("long", "刺松林樹人的樹枝，時常被人收集。");
    }
    setup();
}
