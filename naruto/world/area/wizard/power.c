#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "神之力");
	set("long", @LONG
這個房間存在著一些不可思議的力量，傳說中在這裡施展一些特
殊的禁忌巫術，可以改變這個世界的所有事物，實在是太不可思議了
。在這裡充滿緊張的氣氛，你不由得想趕緊離開。
LONG
	);

	set("exits", ([
		"north" : __DIR__"guildhall",
	]));

	setup();

    load_object("/daemon/board/chat");
}