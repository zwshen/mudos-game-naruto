#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("【"HIR"武卷"HIW"60%"NOR"】智慧+2", ({ "book", "__BOOK__" }));

    set_weight(1);

    if( !clonep() ) {
        set("unit", "個");
        set("value", -1);
        set("long", "一個可以增強武器能力的卷軸。(help combine)");
    }

    // 效果
    set("effect", ([
        "type": "WP",                // 武器類
        "success": 60,              // 成功率
        "int": 2,
    ]) );

    setup();
}
