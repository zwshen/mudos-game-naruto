#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("阿斯瑪", ({ "asma" }));
    set("title", "猿飛");
    set_race("human");
    set_level(70);
    set("camp", "muye");
    set("long", "經常吸煙，而且態度懶散的阿斯瑪，完全不像個忍者，但是他的實力\n"
                "不在卡卡西之下，是木葉村中屈指可數的上忍之一。\n");


    set("age", 27);
    set("gender", "male");

    setup();
}
