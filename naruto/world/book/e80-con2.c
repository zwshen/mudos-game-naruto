#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("【"HIG"防卷"HIW"80%"NOR"】體格+2", ({ "book", "__BOOK__" }));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "個");
        set("value", -1);
        set("no_box", 1);
        set("long", "一個可以增強防具能力的卷軸。(help combine)");
    }
    // 效果
    set("effect", ([
        "type": "EQ",        // 防具類
        "success": 80,       // 成功率
        "con": 2,            // 體格
    ]) );
    setup();
}
