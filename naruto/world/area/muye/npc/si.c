#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("惠比斯", ({ "si" }));
    set_race("human");
    set_level(50);
    set("camp", "muye");
    set("long", "專門培育未來火影人選的精英教師，自信接受自已的教導就是成為火\n"
                "影的最快途徑，目前正在教導第三代火影的孫子。\n");

    set("age", 28);
    set("gender", "male");

    setup();
}
