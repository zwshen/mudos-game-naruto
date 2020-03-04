#include <ansi.h>
#include <room.h>

inherit INN;

/*
void create()
{
	set("short", HIR"Released Workroom "HIY"[Ver 1.0 beta] "NOR);
	set("long", @LONG
    這是一個剛完成的工作站，是供各位巫師作樂用的房間，空閒時
也能來泡茶聊天，生活悠閒，簡直是巫師之中的聖地，聖地之中的天
堂。
LONG);
	set("name", query("short"));
	set("x_axis_size", 8);
	set("y_axis_size", 5);
	setup();
}
*/

void init()
{
	object me, room;

	me = this_player();

	if( !me || !objectp(me) ) return;

	seteuid(geteuid(me));

	room = load_object(__DIR__"workarea.c");

	area_move(room, me, 6, 6);
}
