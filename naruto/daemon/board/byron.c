inherit BULLETIN_BOARD;

void create()
{
        set_name("¤»Ál­·¹a", ({ "byron's board","board" }) );
        set("location", "/u/b/byron/workroom.c");
        set("board_id", "byron");
        set("board_owner","byron");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
