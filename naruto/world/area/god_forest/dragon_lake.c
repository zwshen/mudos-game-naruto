#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "龍潭");
    set("x_axis_size", 21);            // 橫向大小
    set("y_axis_size", 11);            // 縱向大小
    setup();
    set("no_recall", 1);
}
