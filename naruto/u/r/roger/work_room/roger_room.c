#include <room.h>
inherit ROOM;

void create()
{
        set("short", "茅草屋");
        set("long", @LONG
十分簡陋的小地方，隨然雜亂不堪，但卻亂中有序。
古有云：三國亂世三結義，三顧茅蘆請聖賢，莫過於此也。
LONG);
    set("exits", ([ 
        "wizard" : ([ "filename" : __DIR__"guildhall.c",
                       "x_axis" : 13,
                       "y_axis" : 5,
                   ]),
        "south" : ([ "filename" : __DIR__"wizard.c",
                       "x_axis" : 35,
                       "y_axis" : 15,
                  ]),
    ]));
        setup();
}
