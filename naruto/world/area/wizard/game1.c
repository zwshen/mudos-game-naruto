#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�C����(��)");
	set("long", @LONG
�o�O�@���𶢮T�ֳ��ҡA����i���\��@�Ǧn�����F��
LONG);

	set("exits", ([
		"east" : __DIR__"game2",
		"south" : __DIR__"game4",
	]));

    set("objects", ([
    	_DIR_ITEM_"big2.c" : 1,
    ]));

    set("no_fight", 1);
	setup();
}