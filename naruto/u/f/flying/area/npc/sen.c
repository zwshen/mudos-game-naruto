#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("森獸", ({ "sen shou", "sen", "shou" }));
    set_race("human");
    set_level(20);
    
    set("long", "森林中的神秘兇獸，不會主動攻擊，但是集體群居的牠們也不是好惹的。\n"
                 );

    set("age", 70);
    set("gender", "male");

    setup();

    }  

