/* mouse_tooth.c
   木葉村下水道蟑王特別防具...
   write by -Acme-
*/

#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name(YEL"蟑翅"NOR, ({ "cockroach's wings", "wings" }) );

    set_weight(1200);

    setup_cloth();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 105900);
        set("long", "一對巨大的蟑螂翅膀，戴上去後好像會飛一樣。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "dex": 3,
            "evade": 10,
            "wittiness": 10,
            "dodge": 10,
        ]));
    }
    setup();
}