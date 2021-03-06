#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("【"HIG"防卷"HIW"100%"NOR"】全屬性+5", ({ "book", "__BOOK__" }));

    set_weight(1);

    if( !clonep() ) {
        set("unit", "個");
        set("value", -1);
        set("long", "一個可以增強防具能力的卷軸。(help combine)");
    }

    // 效果
    set("effect", ([
        "type": "EQ",                // 防具類
        "success": 100,              // 成功率
        "str": 5, 
        "con": 5,
        "dex": 5,
        "int": 5,
    ]) );

    setup();
}

