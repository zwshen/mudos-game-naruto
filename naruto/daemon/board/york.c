inherit BULLETIN_BOARD;

void create()
{
        set_name("¬ù§J¯d¨¥ª©", ({ "york's board","board" }) );
        set("location", "/u/y/york/workroom");
        set("board_id", "york");
        set("board_owner","york");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
