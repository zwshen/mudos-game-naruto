#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name("旅團雇請單", ({ "paper", "_TEAM_PAPER_" }));
    if( !clonep() ) {
        set("base_unit", "張");
        set("unit", "張");
        set("base_value", 99999999);
        set("base_weight", 100);
        set("long", "一般人根本付不起的天價，雇用幻影旅團成員專用。");
    }
    setup();
}
