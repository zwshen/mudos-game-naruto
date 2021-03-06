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
    return "滅蟑大作戰";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "愛子小姐家因為後院雜草叢生，所以蟑螂也特別多！尤其是大型的\n";
    msg += "蟑螂，每次出現都嚇的愛子小姐跳到桌上半天不敢下來，如果飛起\n";
    msg += "來更是連家都不要了，直接奪門而出。這種心驚膽跳的生活她再也\n";
    msg += "不想過了，決定來次滅蟑行動。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 4;
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
    if( player->query("level") < 4 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/ai.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N非常害怕的大聲尖叫﹗﹗\n"NOR,
        "$N緊張地說道："HIG"走開！蟑螂不要靠近我！\n"NOR,
        "$N對著$n說道："HIG"快點幫我打死牠！\n"NOR,
    });
        
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/muye/npc/cockroach2.c": 15,         // 大蟑螂
        "/world/area/whale_island/npc/cockroach2.c": 15, // 大海蟑螂
        "/world/area/muye/npc/cockroach3.c": 10,         // 巨蟑螂
        "/world/area/whale_island/npc/cockroach3.c": 10, // 巨海蟑螂
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/muye/npc/item/cr_antenna.c": 10,    // 蟑螂觸角
        "/world/area/muye/npc/item/cr_feet.c": 10,       // 蟑螂腳
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
    return "/world/area/muye/npc/ai.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N非常害怕的大聲尖叫﹗﹗\n"NOR,
        "$N害怕地說道："HIG"誰叫$n拿蟑螂的屍體回來！\n"NOR,
        "$N害怕地說道："HIG"任務結束了！趕快帶著蟑螂的屍體離開！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "學習點數 160 點。\n";
    msg += "銀子 300 兩。\n";
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
    player->add_point("learn", 160);
    tell_object(player, HIY"(你獲得了 160 點學習點數。)\n"NOR);
    player->add("bank", 300);
    tell_object(player, HIY"(你獲得了 300 兩銀子。)\n"NOR);
}
