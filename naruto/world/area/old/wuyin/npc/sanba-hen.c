#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("´Ë¤ÚÂû", ({ "sanba hen","hen"  }) );
    set_race("beast");
    set_level(10);

    set("long", "¤@ªþÅº¶Æªº¥ÀÂû¡A¦ý«ç»ò¦³Âû«a¡H¡C\n");

    set("limbs", ({ "Âû«a", "Âû¤ò", "Âû»L", "Âû§¾ªÑ", "Âû¯Ý" }) );
    set("verbs", ({ "bite" }) );
 
    setup();

    carry_money("silver", 1);
    if( random(100) > 60 ) carry_object("/world/area/wuyin/obj/jelly.c");
    if( random(100) > 85 ) carry_object("/world/area/wuyin/eq/cockscomb.c")->wear();


}
