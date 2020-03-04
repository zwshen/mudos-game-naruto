#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name("木造藏", ({ "treasury", "_WOOD_TREASURY_" }));
    if( !clonep() ) {
        set("base_unit", "座");
        set("unit", "座");
        set("base_value", 20);
        set("base_weight", 100);
        set("long", "雕刻樸素的木頭，聽說裡面常會藏一些珍貴寶物。");
    }
    setup();
}
