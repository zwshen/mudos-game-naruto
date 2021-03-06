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
    return "見利忘義";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "你被蛇皇所給的獎勵所吸引....接下了一個殺害人類的可怕任務。\n";
    msg += "希望在完成這個任務之後不會受到自己良心的譴責。\n";

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
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/bone/npc/snake_king.c";  // 蛇皇
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N神情古怪地露出個邪惡的笑容﹐該不會是想做什麼壞事吧。\n"NOR,
        "$N對著$n說道："HIG"想不想接個任務阿？獎勵絕對豐富。\n\n"NOR,
        CYN"$n向$N盤問有關任務的事情...\n"NOR,
        "$N一派輕鬆地笑道："HIG"沒什麼大不了的！不過殺幾個人而已！\n"NOR,
        "$N說道："HIG"想接就來吧！不要就拉倒！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/muye/npc/fishing_man.c": 9,         // 釣客
        "/world/area/echo/npc/girl.c": 1,                // 少女(老張女兒)
        "/world/area/muye/npc/poolman.c": 3,             // 泡湯人
        "/world/area/muye/npc/muye.c": 1,                // 木葉丸
        "/world/area/whale_island/npc/tu-qian-xie.c": 1, // 屠千蟹
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
    return "/world/area/bone/npc/snake_king.c";  // 蛇皇
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N大笑道："HIG"人類有句話叫有錢能使鬼推墨，說的真不錯阿！\n"NOR,
        "$N對著$n說道："HIG"獎勵在這裡，拿了快滾吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習點數 1600 點。\n";
    msg += "銀子 40000 兩。\n";
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
    player->add_point("learn", 1600);
    tell_object(player, HIY"(你獲得了 1600 點學習點數。)\n"NOR);
    player->add("bank", 40000);
    tell_object(player, HIY"(你獲得了 40000 兩銀子。)\n"NOR);
}
