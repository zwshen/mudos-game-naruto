#include <npc.h>
#include <ansi.h>

void create()
{
        set_name(RED"米迦勒"NOR, ({ "michael" }));
        set_race("human");
        set("age", 20);
        set("title", "熾炙天使");
        set("long", "四大天使之一，火天使。\n");
        set("no_fight", 1);
        setup();
}

