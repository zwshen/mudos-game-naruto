#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIM"魂"HIC"玉"NOR, ({ "soul jade", "jade" }));
    if( !clonep() ) {
        set("base_unit", "顆");
        set("unit", "顆");
        set("base_value", -1);
        set("base_weight", 1);
        set("long", "發出五顏六色光芒的玉球，球中好像有流動的水，不停轉動。");
    }
    setup();
}
