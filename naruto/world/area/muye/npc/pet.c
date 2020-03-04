// write by -Acme-
/* pet.c Ãdª«¡G§Ô¤ü */

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("¤pª¯", ({ "dog" }));
    set_race("beast");
    set_level(1);
    set("no_fight", 1);
    set("age", 1);
    set("long", "¦N¥Ð®a¾iªºª¯¡C\n");
    setup();
}

int follow_me(object ob, string dir)
{
	object leader;
    this_object()->add("move_count", 1);
    if( objectp(leader = this_object()->query_leader()) )
        leader->start_busy(2);
    return ::follow_me(ob, dir);
}
