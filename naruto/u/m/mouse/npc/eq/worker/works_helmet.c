#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(YEL"安全帽"NOR, ({ "Safe helmet", "helmet" }) );

    set_weight(1500);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 10);
        set("long", "工人所帶的帽子，上面寫著『安全第一』");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 10,
            "exact": 30,
        ]));
    }

    setup();
}
