#include <ansi.h>
#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
        set_name(HIW"白虎爪"NOR, ({ "tiger wrist","wrist" }) );
        set_weight(10000);
        setup_wrist_eq();

        if( !clonep() ) {
                set("unit", "對相當沉重的");
        set("value", 600);
                set("long", "相傳是四大聖獸【白虎】的牙所製成的爪子，有著最佳防備與攻勢構造，往往能讓敵人措手不及。\n");
                set("wear_as", "wrist_eq");
                set("apply_armor/wrist_eq", ([
                        "armor": 10,
                        "attack": 10,
                ]));
        }

        setup();
}
