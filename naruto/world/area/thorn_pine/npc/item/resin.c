#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"樹脂"NOR, ({ "resin" }));
    if( !clonep() ) {
        set("base_unit", "罐");
        set("unit", "罐");
        set("base_value", 300);
        set("base_weight", 10);
        set("long", "刺松林樹人的樹脂，少量可以養顏美容。");
    }
    setup();
}
