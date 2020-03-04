#include <ansi.h>

inherit BULLETIN_BOARD;

void create()
{
	set_name(HIW"§Å®v¤½§iªO"NOR, ({ "wizard board", "board" }) );
	set("location", "/world/area/wizard/guildhall");
	set("board_id", "wizard");
	set("NO_PLAYER_POST", 1);
	setup();
        set("capacity", 999);
	replace_program(BULLETIN_BOARD);
}
