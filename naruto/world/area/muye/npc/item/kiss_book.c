#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(YEL"親熱天堂"NOR, ({ "kiss heaven book", "book", "_KISS_" }));
    set_weight(1);
    if( !clonep() ) {
        set("middle_test", 2);
        set("unit", "個");
        set("value", 30000);
        set("long", "一本兒童不宜的不良小說。");
    }

    setup();
}
