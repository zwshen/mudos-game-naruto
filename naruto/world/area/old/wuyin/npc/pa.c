#include <npc.h>

inherit F_VILLAGER;

void create()
{
        set_name("陸難趴", ({ "lu lan pa","pa" }) );
        set_race("human");
        set_level(20);
        set("title","茶皇");
        set("age", 70);
        set("long", "茶中之皇陸難趴，「茶莖」這本書就是他的著作，相當有名。\n");

        setup();
        carry_object(__DIR__"obj/tea-book.c");
}
