#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIW"巨大珍珠"NOR, ({ "pearl" }));
    if( !clonep() ) {
        set("base_unit", "顆");
        set("unit", "顆");
        set("base_value", 3000);
        set("base_weight", 200);
        set("long", "閃亮的大顆珍珠，貴婦和商人們的最愛。\n");
    }
    setup();
}
