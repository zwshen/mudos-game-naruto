#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name(HIW"防"HIB"滑"NOR"鞋", ({ "Crampon", "crampon" }) );

    set_weight(1500);

    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 10);
        set("long", "防滑的工作鞋，減少工地危險發生的機率。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 10,
            "evade": 10,
            "wittiness": 10,
        ]));
    }
    setup();
}
