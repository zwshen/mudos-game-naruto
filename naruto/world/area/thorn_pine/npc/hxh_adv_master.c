/* guild: hunter  獵人 */
// write by Tmr 2005/10/22
// 增加念系sk lv 160   by mouse 2007/4/24

#include <npc.h>

inherit F_VILLAGER;
inherit F_TRAINER;    // 訓練導師

void create()
{
    set_name("藍調希凡", ({ "blue xi fan", "fan"}) );
    set_race("human");
    set_level(30);
    set_class("hxh_intermediate");  //有照獵人
    set("age", 40);
    set("camp", "hunter");
    set("title", "獵人執証導師");
    set("gender","female");
    set("long",@long
藍調希凡是一位有名的獵人二階執証導師，也是有名的念能力者，精通有照
獵人常見的六大系特殊技能。可以利用train 指令來學習技能。使用 list 
指令查詢可學習的技能列表
long
);

    // 只輔導獵人
    set("guild", "hunter");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("machine gun", 1, 21, 100, "hunter", 0);         // 放出系：雙手機關槍
    set_train_with_camp("chamber fish", 1, 21, 100, "hunter", 0);        // 具現系：密室念魚
    set_train_with_camp("chain lighting", 1, 21, 100, "hunter", 0);      // 變化系：連鎖閃電
    set_train_with_camp("frost closed ball", 1, 21, 100, "hunter", 0);   // 變化系：冰封球
    set_train_with_camp("variation", 1, 10, 160, "hunter", -1);          // 變化系
    set_train_with_camp("strength", 1, 10, 160, "hunter", -1);           // 強化系
    set_train_with_camp("operation", 1, 10, 160, "hunter", -1);          // 操作系
    set_train_with_camp("emit", 1, 10, 160, "hunter", -1);               // 放出系
    set_train_with_camp("concrete", 1, 10, 160, "hunter", -1);           // 具現系
    set_train_with_camp("special", 1, 10, 160, "hunter", -1);            // 特質系
    setup();

    // 人物本身的技能設定
    set_skill("solid", 100);               // 念技：堅
    map_skill("parry", "solid");    
}
