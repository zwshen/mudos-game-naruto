#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIW"微粒"NOR, ({ "particle" }));
    if( !clonep() ) {
        set("base_unit", "點");
        set("unit", "點");
        set("base_value", 1);
        set("base_weight", 1);
        set("long", "飄散在空氣中的細小粒子，沒什麼用。");
    }
    setup();
}
