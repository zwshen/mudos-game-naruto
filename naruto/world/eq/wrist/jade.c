#include <ansi.h>
#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name(GRN"玉手環"NOR, ({ "jade wrist", "wrist" }) );
    set_weight(100);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "個");
        set("value", 1600);
        set("long", "一個十分別緻的玉手環，上頭的紋路很規則。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 2,
            "con": 2
        ]));
    }

    setup();
}
