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
    return "軟泥";
}

// 任務描述
string getDetail() {
    string msg;

        msg  = "你必須將梟所要求的各種紙張帶回來給他。「紙繪」本身就是一種閃\n";
        msg += "躲的技巧因為像紙張一樣遇到風就會被吹開，因此一般的攻擊幾乎打\n";
        msg += "不到能善用紙繪的高手，軟泥是紙繪的特殊技能，讓身體就算被打中\n";
        msg += "，也能藉著泥巴般的身體再次閃過攻擊。\n";

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
    if( player->query_skill("paper slime", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sifa_isle/npc/xiao.c";   // 梟
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"喳叭叭！貓頭鷹的技能不是平常人能學的！\n"NOR,
        "$N說道："HIG"$n要幫我拿回這些種類的紙我才教$n！喳叭叭！\n"NOR,
        "$N說道："HIG"我絕對不會說那個天氣預測表是要找木葉村的「童角」！\n"NOR,
        "$N說道："HIG".....\n"NOR,
        "$N說道："HIG"又說溜嘴了！喳叭叭！\n"NOR,
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
        "/world/area/ship/npc/item/paper.c": 1,     // 天氣預期表
        "/world/area/lake/npc/item/paper.c": 1,     // 機關紙
        "/world/area/lake/npc/item/paper2.c": 1,    // 信紙
        "/world/area/old_forest/npc/item/map.c": 1, // 古老森林地圖
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
    return "/world/area/sifa_isle/npc/xiao.c";   // 梟
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"喳叭叭！居然都被$n找到了！\n"NOR,
        "$N說道："HIG"沒辦法只好教$n軟泥吧！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIW"紙繪•軟泥"NOR"」\n";
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
    player->set_skill("paper slime", 2);
    tell_object(player, HIY"(你學會了紙繪應用技軟泥)\n"NOR);
}
