#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("【"HIR"武卷"HIW"100%"NOR"】力量+5", ({ "book", "__BOOK__" }));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "個");
        set("value", -1);
        set("long", "一個可以增強武器能力的卷軸。(help combine)");
    }
    set("effect", ([
        "type": "WP",                // 武器類
        "success": 100,              // 成功率
        "str": 5,
    ]) );
    setup();
}
