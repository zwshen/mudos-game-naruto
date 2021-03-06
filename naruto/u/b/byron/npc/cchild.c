#include <npc.h>
inherit F_FIGHTER;
void create()
{
    set_name("小孩", ({ "child" }));
    set_race("human");
    set_level(99);
    set_stat_maximum("hp",1); 
    set_stat_maximum("ap",1);
    set_stat_maximum("mp",1);
    set_attr("str",1);
    set_attr("con",1);
    set_attr("dex",1);
    set_attr("int",1);
    set("age", 6+random(10));
    set("long", "一個流著鼻涕的小孩，不知在哪玩得全身髒兮兮。\n");
    setup();
    set_temp("apply/attack",-4060);
    set_temp("apply/intimidate",-200);     // 攻擊能力
    set_temp("apply/armor",-2233);         // 防禦力量
    set_temp("apply/wittiness",-100);      // 防禦能力
    set_temp("apply/exact",-100);          // 命中率
    set_temp("apply/evade",-100);          // 迴避率
    set_skill("combat",1);
    set_skill("parry",1);
    set_skill("dodge",1);
    set_skill("savage hit",1);
    set_skill("continual hit",1);
    set_skill("heavy hit",1);
}

