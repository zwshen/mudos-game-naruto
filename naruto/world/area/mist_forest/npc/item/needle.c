#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIG"毛針"NOR, ({ "needle" }));
    if( !clonep() ) {
        set("base_unit", "根");
        set("unit", "根");
        set("base_value", 2);
        set("base_weight", 1);
        set("long", "適應環境而長成的樹之葉子，前端硬如尖針，身子卻柔軟似毛。");
    }
    setup();
}