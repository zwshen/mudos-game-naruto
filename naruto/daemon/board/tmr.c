inherit BULLETIN_BOARD;

void create()
{
          set_name("µ²Ã·°O¨Æ", ({ "memory board","board" }) );
        set("location", "/u/t/tmr/workroom");
        set("board_id", "tmr");
        set("board_owner","tmr");
        setup();
        set("capacity", 200);
        replace_program(BULLETIN_BOARD);
}

