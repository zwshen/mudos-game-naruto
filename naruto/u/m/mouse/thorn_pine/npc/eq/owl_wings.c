#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name(HIY"梟之翼"NOR, ({ "owl wings", "wings" }) );
    set_weight(1200);
    setup_cloth();
    if( !clonep() ) {
        set("unit", "雙");
        set("value", 187700);
        set("long", "蒼之梟的翅膀，穿上後隨手一振就能高飛數十丈。\n");
        // wear穿著敘述, unequip脫下敘述
        set("wear_msg", "$N"HIC"將"NOR"$n"HIC"披在身上，四周刮起一陣旋風。\n"NOR);
        set("unequip_msg", "$N"HIC"卸除"NOR"$n"HIC"的裝備。\n"NOR);
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 15,
            "dex": 4,
            "evade": 15,
            "wittiness": 10,
        ]));
    }
    setup();
}
