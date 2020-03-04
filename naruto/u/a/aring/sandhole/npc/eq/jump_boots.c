#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name(BCYN"刺刺彈力鞋"NOR, ({ "jump boots", "boots" }) );

    set_weight(1200);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 2750);
        set("long", "穿上它，便可體會走gonna飛的感覺。\n");
        set("wear_as", "feet_eq");
        set("wear_msg", HIY"$N穿上$n"HIY"了後，便高聲唱著： 暈喜口愛ㄟ小輝俠∼∼\n"NOR);
        set("apply_armor/feet_eq", ([
            "str": -5,
            "evade": 5,
            "dex": 2,
            "armor": 4,
        ]));
    }

    setup();
}

