#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"狐掌"NOR, ({ "fox paw", "paw", "_FOX_PAW_" }));
    if( !clonep() ) {
        set("base_unit", "隻");
        set("unit", "隻");
        set("base_value", 500);
        set("base_weight", 300);
        set("long", "狐熊的手掌，上面的爪子非常銳利。\n");
    }
    setup();
}
