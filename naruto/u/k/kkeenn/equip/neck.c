#include <ansi.h>
#include <armor.h>
inherit F_NECK_EQ;
void create()
{
    set_name(BRED+HIR"血繼女護"NOR, ({ "blood necklace", "necklace" }) );
    set_weight(100);
    setup_neck_eq();
    if( !clonep() ) {
        set("unit", "條");
        set("value", 0);
        set("long", "具有神秘功效的項鍊\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "dex": 5,
            "str": 5,
            "int": 5,
            "con": 5,
            "armor": 20,
]) );
        set("wear_msg",RED+"$N帶上"+name()+RED"的同時，$N的背後出現了一個貌似女性的紅色氣體！\n"NOR);
    }

    setup();
}


