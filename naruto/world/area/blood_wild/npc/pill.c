#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("藥山洨", ({ "pill master", "master" }));
    set_race("human");
    set("nickname", "山之男");
    set_level(1);
    set("long", "一臉流氓樣的男人，左臉夾還有一片被火燒傷的疤痕。全身充滿了濃\n"
                "濃的草藥味，在小屋子中不停地拿起不名藥材嘗味，但是兇神惡煞的\n"
                "樣子感覺實在不像是救人濟世的醫生。\n");
    set("age", 45);
    set("gender", "male");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "say 聽說師兄在天上人間開業了。" :),
        (: command, "say 藥材藥材..." :),
    }) );
    setup();
}
