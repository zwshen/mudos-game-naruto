
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIY"鏟子"NOR, ({ "shovel"}));
    set_weight(3);
    if( !clonep() ) {
        set("unit", "把");
        set("value", 10000);
        set("long", "一把看起來很硬的鏟子，不知道有何作用...\n");
    }
    setup();
}
