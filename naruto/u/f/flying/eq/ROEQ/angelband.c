#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name(HIW"天使髮圈"NOR, ({ "Angel band" ,"band"}) );

    set_weight(500);

    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 5000);
        set("long", "有天使之翼附在上面的頭飾，神聖的。可能是從天堂啟發穿戴者的靈\n"
     "魂進而增加敏捷，祝福與保護心靈的自由來防止惡魔的力量侵入。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 8,
            "int": 1,
            "dex": 1,
        ]));
    }

    setup();
}

