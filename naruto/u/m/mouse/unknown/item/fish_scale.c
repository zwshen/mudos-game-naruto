#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name("魚鱗", ({ "fish scale", "scale", "_FISH_SCALE_" }));
    if( !clonep() ) {
        set("base_unit", "塊");
        set("unit", "塊");
        set("base_value", 100);
        set("base_weight", 700);
        set("long", "沼魚的鱗片，外表光滑，卻硬度十足。\n");
    }
    setup();
}
