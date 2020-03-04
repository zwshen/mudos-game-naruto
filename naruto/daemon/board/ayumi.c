#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name(YEL"Delphi"HIK"¹ý©³¬ã¨s"NOR, ({ "Delphi book","book" }) );
        set("location", "/u/a/ayumi/workroom");
        set("board_id", "ayumi");
        set("board_owner","ayumi");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

