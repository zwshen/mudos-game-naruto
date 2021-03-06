#include <ansi.h>

void create() { seteuid(getuid()); }

// 說明此檔是任務，這個函式不需要變動
int isQuest() { return 1; }

/* 此任務是否能重複解  return 0  不能重複
                       return 1  可重複
   建議最好設定不能重複。
 */
int isNewly() { return 0; }

// 任務名稱
string getName() {
    return "第二專長";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "捕魚人有感要是哪天沒魚可捕，那自己豈不是無事可做？因此決定\n";
    msg += "學習第二專長，性質與捕魚相似的「捕螃蟹」不過捕螃蟹也是一門\n";
    msg += "高深的技術，沒辦法無師自通的捕魚人為此煩惱不已。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 2;
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
    if( player->query("level") < 2 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/fishing_master.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N喃喃自語："HIG"螃蟹怎麼這麼難抓呢！\n"NOR,
        "$N喃喃自語："HIG"我本來還以為跟抓魚一樣呢...\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/whale_island/npc/crab.c": 20,  // 小螃蟹
        "/world/area/whale_island/npc/crab2.c": 6,  // 螃蟹
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    return ([]);
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
    return "/world/area/muye/npc/fishing_master.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N瞠目結舌，好像看到了一件不可思議的事。\n"NOR,
        "$N對著$n說道："HIG"如何抓好螃蟹上下集！\n"NOR,
        "$N對著$n說道："HIG"要送給我嗎！太感謝了！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "學習點數 140 點。\n";
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
void reward(object player, object npc) {
    player->add_point("learn", 140);
    tell_object(player, HIY"(你獲得了 140 點學習點數。)\n"NOR);
}
