#include <ansi.h>
#include <room.h>

inherit AREA;

void create()
{
	set("short", HIR"Released Workroom "HIY"[Ver 1.0 beta] "NOR);
	set("long", @LONG
    這是一個剛完成的工作站，是供各位巫師作樂用的房間，空閒時
也能來泡茶聊天，生活悠閒，簡直是巫師之中的聖地，聖地之中的天
堂。
LONG);
	set("name", query("short"));
	set("x_axis_size", 3);
	set("y_axis_size", 3);
	setup();
}
