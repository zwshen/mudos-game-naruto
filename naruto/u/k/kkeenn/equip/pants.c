#include <ansi.h>
#include <armor.h>
inherit F_PANTS;
void create()
{
    set_name(BRED+HIR"血繼月護"NOR, ({ "blood pants", "pants" }) );
    set_weight(100);
    setup_pants();
    if( !clonep() ) {
        set("unit", "件");
        set("value", 0);
        set("long", "具有神秘功效的武術褲\n");
        set("wear_as", "pants");
        set("apply_armor/pants", ([
            "dex": 5,
            "str": 5,
            "int": 5,
            "con": 5,
            "armor": 20,
            ]) ); 
        set("wear_msg",RED+"$N穿上"+name()+RED"的同時，四周彷彿漂浮著紅色的火焰！\n"NOR);
    }

    setup();
}


