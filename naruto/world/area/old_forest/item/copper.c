#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(YEL"銅礦"NOR, ({ "copper", "_COPPER_" }));
    if( !clonep() ) {
        set("base_unit", "塊");
        set("unit", "塊");
        set("base_value", -1);
        set("base_weight", 50);
        set("long", "接近土色的軟質銅礦，是強化武器韌性不可缺少的礦物。");
    }
    setup();
}
