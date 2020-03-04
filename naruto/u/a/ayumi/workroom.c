#include <ansi.h>
#include <room.h>

// 設成INN者，會自動成為非戰區，並且是重生點
inherit INN;

void create()
{
    set("short", HIB"依雨星辰"NOR);
    set("long", "進門前請先敲門= =a。\n");
    set("exits", ([
        "wizard" : "/world/area/wizard/guildhall.c", 
        "south" : ([ "filename" : "/world/area/wizard/wizard.c",
                       "x_axis" : 27,
                       "y_axis" : 15,
                  ]),
    ]));

    setup();
    load_object("/daemon/board/ayumi");
}
