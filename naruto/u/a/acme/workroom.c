/* write by -Acme- */

#include <ansi.h>
#include <room.h>

// 設成INN者，會自動成為非戰區，並且是重生點
inherit INN;

void create()
{
    set("short", "流螢舞空");
    set("long", "一個相當神秘的地方，這裡藏著一堆稀奇古怪的事物。\n");
    set("exits", ([
        "wizard" : "/world/area/wizard/guildhall.c", 
        "south" : ([ "filename" : "/world/area/wizard/wizard.c",
                       "x_axis" : 23,
                       "y_axis" : 15,
                  ]),
    ]));

    setup();
    load_object("/daemon/board/acme");
}