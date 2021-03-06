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
    return "吃腦補腦";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "鯨魚島的老婆婆進來腦筋不太靈光，常常忘東忘西的，後院雜草叢\n";
    msg += "生，也是因為記性不好，早上起床想說去拔草，洗完臉就忘了。所\n";
    msg += "以要根除這個問題，老婆婆決定吃腦補腦，回復記憶力。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 5;
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
    if( player->query("level") < 5 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/whale_island/npc/oldwoman.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"最近腦袋好像有點不太靈光！\n"NOR,
        CYN"$N重重地拍了一下腦袋, 似乎想到了什麼主意.\n"NOR,
        "$N對著$n說道："HIG"能不能幫老婆婆我拿些補腦的東西呢？\n"NOR,
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
        "/world/area/muye/npc/item/turtle_head.c": 10,        // 龜頭
        "/world/area/old_forest/npc/item/monkey_brain.c": 10, // 猴腦
        "/world/area/echo/npc/item/brain.c": 20,              // 鼠腦
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
    return "/world/area/whale_island/npc/oldwoman.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N興奮地說道："HIG"哈哈！吃了這些我也能成為天才啦！\n"NOR,
        "$N對著$n說道："HIG"不過到底要怎麼料理呢？\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習點數 220 點。\n";
    msg += "銀子 100 兩。\n";
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
    player->add_point("learn", 220);
    tell_object(player, HIY"(你獲得了 220 點學習點數。)\n"NOR);
    player->add("bank", 100);
    tell_object(player, HIY"(你獲得了 100 兩銀子。)\n"NOR);
}
