inherit BULLETIN_BOARD;

void create()
{
        set_name("¦Ì¯S¯d¨¥©±", ({ "mite board", "board" }) );
        set("location", "/world/area/whale_island/mite_hotel");
        set("board_id", "_MITE_");
        setup();
        set("capacity", 200);
        replace_program(BULLETIN_BOARD);
}

