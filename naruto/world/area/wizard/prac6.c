#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "練習場(６)");
	set("long", @LONG
這裡擺放了幾個假人，可以在這裡練技格鬥技能。
LONG);

	set("exits", ([
        "east" : ([ "filename" : __DIR__"wizard.c",
                     "x_axis" : 13,
                     "y_axis" : 36,
                  ]),		
		"north" : __DIR__"prac3",		
		"west" : __DIR__"prac5",		
		"south" : __DIR__"prac9",		
	]));

    set("objects", ([
    	_DIR_NPC_"stake.c": 4,
    ]));

	setup();
}