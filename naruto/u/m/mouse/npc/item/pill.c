#include <ansi.h>

inherit F_FOOD;

void create()
{
    set_name(HIK"黑心"HIW"白皮丹"NOR, ({ "blackwhite pill" ,"pill"}));
    if( !clonep() ) {
        set("unit", "顆");
        set("base_unit", "顆");
        set("base_value", 1000000);
        set("base_weight", 1);
        set("food_stuff", 1);
        set("long", "白色外皮包著黑色丹藥，有著酸甜苦辣麻鹹澀等味道，功能不明。\n");
        set("condition", ([ 
            "apheal4": ([ "duration": 140 ]),
            "hpheal4": ([ "duration": 140 ]),
            "mpheal4": ([ "duration": 140 ]),
            "apheal3": ([ "duration": 160 ]),
            "hpheal3": ([ "duration": 160 ]),
            "mpheal3": ([ "duration": 160 ]),
            "apheal2": ([ "duration": 180 ]),
            "hpheal2": ([ "duration": 180 ]),
            "mpheal2": ([ "duration": 180 ]),
            "apheal1": ([ "duration": 200 ]),
            "hpheal1": ([ "duration": 200 ]),
            "mpheal1": ([ "duration": 200 ]),
        ]));
    }
    setup();
}
