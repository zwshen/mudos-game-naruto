#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"蜘蛛眼睛"NOR, ({ "spider eye", "eye" }));
    if( !clonep() ) {
        set("base_unit", "對");
          set("base_value", 15);
        set("base_weight", 100);
        set("long", "一對剛拔下來的蜘蛛眼睛。\n");
    }
    setup();
}

