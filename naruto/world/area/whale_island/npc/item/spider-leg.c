#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIK"蜘蛛腿"NOR, ({ "spider leg", "leg" }));
    if( !clonep() ) {
        set("base_unit", "支");
            set("base_value", 10);
        set("base_weight", 100);
        set("long", "一支剛斬下來的蜘蛛腿。\n");
    }
    setup();
}

