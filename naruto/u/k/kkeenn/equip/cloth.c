#include <ansi.h>
#include <armor.h>
inherit F_CLOTH;
void create()
{
    set_name(BRED+HIR"血繼星護"NOR, ({ "blood cloth", "cloth" }) );
    set_weight(100);
    setup_cloth();
    if( !clonep() ) {
        set("unit", "件");
        set("value", 0);
        set("long", "具有神秘功效的內襯\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "dex": 5,
            "str": 5,
            "int": 5,
            "con": 5,
            "armor": 80,
            "exact": 5,
            "evade": 20,
            "wittiness": 20,
            "dodge": 50,
        "exact": 1000,
        "evade": 1000,
        "intimidate": 1000,
        "wittiness": 1000,
        "move": 1000,
        "carriage": 1000,

        ]));
        set("wear_msg",RED"$N穿上"+name()+RED"四周散發著若有若無的紅光！\n"NOR);
    }

    setup();
}

