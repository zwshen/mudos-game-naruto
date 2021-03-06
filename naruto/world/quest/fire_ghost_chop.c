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
    return "燭臺火焰之舞";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "你想和索隆學習「"HIR"燒鬼斬"NOR"」的技能，但是索隆一時間忘記當初是在什\n";
    msg += "麼情況下才使用出這招，因而無法教導你。因此你只好照著索隆所給\n";
    msg += "的清單去尋找物品，希望能喚醒索隆的記憶。\n";

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
    if( player->query_skill("fire ghost chop", 1) ) return 0;
    if( player->query_class() == "work_sea" ) return 0;
    if( player->query_class() == "little_sea" ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/ship/npc/zoro.c";   // 索隆
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"什麼？想學燒鬼斬？\n"NOR,
        "$N一臉疑惑說道："HIG"當初是怎麼用那招的阿...有點記不起來了...\n"NOR,
        "$N說道："HIG"好像記得有繩子...拳擊手套...還有..油？\n"NOR,
        "$N說道："HIG"$n幫忙把這些東西找來吧，也許能喚醒我的記憶。\n"NOR,
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
        "/world/eq/hand/fist.c": 1,               // 拳擊手套
        "/world/eq/belt/cord.c": 1,               // 繩子
        "/world/area/benthal/npc/food/oil.c": 20, // 魚肝油
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
    return "/world/area/ship/npc/zoro.c";   // 索隆
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N低頭沉思著...\n"NOR,
        "$N忽然說道："HIG"對了！就是那個Ｍｒ３蠟燭男！\n"NOR,
        "$N說道："HIG"因為騙人布的機智用澆上油的繩子點火才救了我們。\n"NOR,
        "$N對著$n說道："HIG"我想起來了，這就教你如何使用燒鬼斬。\n\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIR"燒鬼斬"NOR"」\n";
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
    player->set_skill("fire ghost chop", 2);
    tell_object(player, HIY"(經過索隆的指導之後，你將燒鬼斬學會了。)\n"NOR);
}
