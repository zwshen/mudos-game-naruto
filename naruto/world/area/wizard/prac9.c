#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "練習場(９)");
	set("long", @LONG
這裡擺放了幾個假人，可以在這裡練技格鬥技能。
LONG);

	set("exits", ([
		"north" : __DIR__"prac6",
		"west" : __DIR__"prac8",
	]));

    set("objects", ([
    	_DIR_NPC_"stake.c": 4,
    ]));

	setup();
}