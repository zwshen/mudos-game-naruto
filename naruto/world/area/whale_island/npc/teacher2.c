/* guild: hunter  獵人 */
// write by Tmr 2005/10/22

#include <npc.h>

inherit F_VILLAGER;
inherit F_TRAINER;    // 訓練導師

void create()
{
    set_name("馬不繞", ({ "ma bu-rao", "rao", "teacher"}) );
    set_race("human");
    set_level(30);
    set_class("hxh_intermediate");  //有照獵人
    set("age", 25);
    set("camp", "hunter");
    set("title", "獵人執証導師");
    set("gender","female");
    set("long", "馬不繞是一位有名的獵人執証導師，也是有名的念能力者，精通六大系的\n"
                "常用技能。可以利用train 指令來學習技能。使用 list 指令查詢可學習\n"
                "的技能列表。\n" );

    // 只輔導獵人
    set("guild", "hunter");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("finger-guessing fist", 1, 10, 100, "hunter", -1);  // 邪拳
    set_train_with_camp("solid", 1, 10, 120, "hunter", -1);                 // 堅 
    set_train_with_camp("body strength", 1, 10, 100, "hunter", -1);         // 肉體強化
    set_train_with_camp("psychical bullet", 1, 10, 100, "hunter", -1);      // 念彈
    set_train_with_camp("holy hand", 1, 10, 100, "hunter", -1);             // 聖療之手
    set_train_with_camp("harm touch", 1, 10, 100, "hunter", -1);            // 傷害之觸
    set_train_with_camp("blood-cell revive", 1, 10, 100, "hunter", -1);     // 細胞再生
    set_train_with_camp("fire variation", 1, 10, 100, "hunter", -1);        // 火念力變化
    set_train_with_camp("ice variation", 1, 10, 100, "hunter", -1);         // 冰念力變化
    set_train_with_camp("electric variation", 1, 10, 100, "hunter", -1);    // 電念力變化
    set_train_with_camp("eaves family", 1, 10, 100, "hunter", -1);          // 屋簷下的一家人

    setup();

    // 人物本身的技能設定
    set_skill("solid", 100);               // 念技：堅
    map_skill("parry", "solid");    
}
