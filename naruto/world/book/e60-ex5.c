#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("【"HIG"防卷"HIW"60%"NOR"】命中能力+5", ({ "book", "__BOOK__" }));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "個");
        set("value", -1);
        set("no_box", 1);
        set("long", "一個可以增強防具能力的卷軸。(help combine)");
    }
    // 效果
    set("effect", ([
        "type": "EQ",   // 防具類
        "success": 60,  // 成功率
        "exact": 5,     // 命中+5
    ]) );
    setup();
}
