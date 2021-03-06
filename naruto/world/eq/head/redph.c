#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIR"紅色"HIW"羽毛頭巾"NOR, ({ "red plume hood", "hood" }) );

    set_weight(1000);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 650);
        set("long", "一條相當有個人風格的頭巾，上頭還插著幾根紅色羽毛。");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
        	"armor": 2,
            "exact": 3,
        ]));
    }

    setup();
}
