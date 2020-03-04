#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIM"»jµï¬r²G"NOR, ({ "spider venom", "venom","__QUEST_D_2__" }));
    if( !clonep() ) {
        set("base_unit", "²~ ");
        set("base_value", 45);
        set("base_weight", 100);
        set("long", "¤@²~­è±Ä¶°¨Óªº»jµï¬r²G¡C\n");
    }
    setup();
}

