#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(YEL"肥腿章"NOR, ({ "fat taco","taco" }) );
    set_race("beast");
    set_level(19);

    set("long", "一隻瀕臨絕種的生物，常常棲息在水之國的海岸邊，一附傭懶的模樣。\n");

    set("limbs", ({ "觸腳", "嘴巴", "頭部", "腹部" }) );
    set("verbs", ({ "bite" }) );
 
    set("chat_chance", 3);
    set("chat_msg", ({
        "肥腿章滑溜溜的在地上翻滾。\n",
                (: random_move :),
        }));

    setup();

    carry_money("silver", 20);
    if( random(100) > 60 ) carry_object("/world/area/wuyin/obj/taco-burn.c");
    if( random(100) > 95 ) carry_object("/world/area/wuyin/eq/octopus-cap.c");

}
