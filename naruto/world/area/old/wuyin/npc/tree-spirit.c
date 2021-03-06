#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(GRN"樹小妖"NOR, ({ "tree spirit","tree","spirit" }) );
    set_race("beast");
    set_level(17);

    set("long", "被高人施展過高等法術而會走路的樹木，一有敵人接近就會自動攻擊敵人。\n");

    set("limbs", ({ "樹幹", "樹枝", "樹莖", "樹頭", "樹葉" }) );
    set("verbs", ({ "bite" }) );
    
    set("attitude", "aggressive");         // 主動攻擊

    setup();

    if( random(100) > 60 ) carry_object("/world/wp/rattan.c")->wield("lefthand");
    if( random(100) > 60 ) carry_object("/world/wp/rattan.c")->wield("righthand");

}

