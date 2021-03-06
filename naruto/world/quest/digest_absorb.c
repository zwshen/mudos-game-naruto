#include <ansi.h>

// 說明此檔是任務，這個函式不需要變動
int isQuest() { return 1; }

/* 此任務是否能重複解  return 0  不能重複
                       return 1  可重複
   建議最好設定不能重複。
 */
int isNewly() { return 1; }

// 任務名稱
string getName() {
    return "生命歸返";
}

// 任務描述
string getDetail() {
    string msg;

        msg  = "「生命歸返」是一種特殊的武術，經由腦部的控制改變身體的狀態，\n";
        msg += "初學者可以促進新陳代謝，增進消化和吸收的能力，使血液循環更加\n";
        msg += "快速，達到加速體力回復的提升。為了讓身體隨時習慣生命歸返使用\n";
        msg += "時的狀態，隈取要求你帶回一些能夠回復體力的藥品。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 20;
}

/* 接受任務的前置條件，可能是
        1. 等級需求
        2. 職業需求
        3. 種族需求
        4. 已完成某些任務需求
    等等，應可以自由發揮才是。
    回傳非零值表示符合條件。
 */
int preCondition(object player) {
    if( player->query("guild") != "piece" ) return 0;
    if( player->query_skill("digest absorb", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sifa_isle/npc/wei.c";   // 隈取
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"呦伊呦伊！要學生命歸返！\n"NOR,
        "$N說道："HIG"生命歸返！需要強紉的身體！呦伊呦伊！\n"NOR,
        "$N說道："HIG"需要一些回復體力的藥品！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    return ([]);
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/drug/hp_heal.c": 10,                       // 體力丸
        "/world/drug/hp_heal2.c": 2,                       // 大體力丸
        "/world/area/thorn_pine/npc/item/hp_help.c": 1,    // 體力急救
    ]);
    return item;
}

// 完成任務的條件除了系統提供的
// 1. 搜集物品
// 2. 殺了足夠數量的怪物之外
// 有需要的話，還可以自訂完成任務條件
// return 1, 為滿足條件, return 0;為失敗
int postCondition(object player, object npc)
{
    return 1;
}

// 完成任務的NPC  (以檔名來識別)
string getRewarder() {
    return "/world/area/sifa_isle/npc/wei.c";   // 隈取
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"呦伊呦伊！讓我來...！\n"NOR,
        "$N說道："HIG"教$n吧！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIW"消化吸收"NOR"」\n";
    return msg;
}

/*  任務獎勵
    獎勵應該能自由發揮，如：
        1. 獲得經驗
        2. 獲得物品
        3. 獲得短暫Buff
        4. 習得某技能
        5. 更改玩家狀態, ex: 轉職
 */
void reward(object player, object npc)
{
    player->set_skill("digest absorb", 2);
    tell_object(player, HIY"(你的身體似乎能夠負擔生命歸返了)\n"NOR);
}
