#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name("古董花瓶", ({ "vase", "_OLD_VASE_" }));
    if( !clonep() ) {
        set("base_unit", "個");
        set("unit", "個");
        set("base_value", 20);
        set("base_weight", 100);
        set("long", "看起來有段歷史的花瓶，上面有點裂紋。");
    }
    setup();
}
