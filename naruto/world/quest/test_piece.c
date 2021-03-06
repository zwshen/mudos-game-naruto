#include <ansi.h>

// 說明此檔是任務，這個函式不需要變動
int isQuest() { return 1; }

/* 此任務是否能重複解  return 0  不能重複
                       return 1  可重複
   建議最好設定不能重複。
 */
int isNewly() { return 0; }

// 任務名稱
string getName() {
    return "卡蒙的心事";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "寶箱人卡蒙在小荒島上待了幾十年，除了守護夢中的寶藏之外還\n";
    msg += "多了一個新的願望，就是守護島上的各種珍獸們的安全，不過在\n";
    msg += "搶奪寶箱的海賊中居然有許多人是馴獸師，他們已經馴服了很多\n";
    msg += "的珍獸，還藉此接近其他的珍獸準備大舉捕捉販賣，因此卡蒙忍\n";
    msg += "痛下了一個決定，希望有人能把那群被馴服的珍獸清除。\n";

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
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/barren_isle/npc/ka.c";  // 寶箱人卡蒙
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N正盯著$n看﹐不知道打些什麼主意。。\n"NOR,
        "$N說道："HIG"可惡的海賊居然打上珍獸的主意了...\n"NOR,
        "$N說道："HIG"那些被馴服的珍獸還會偷襲其他珍獸...\n"NOR,
        "$N說道："HIG"$n能幫助我清除那些被馴服的珍獸嗎？\n"NOR
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/barren_isle/npc/monkey.c": 10,  // 飛天猴
        "/world/area/barren_isle/npc/pig.c": 10,     // 獅頭豬身
        "/world/area/barren_isle/npc/rabbit.c": 10,  // 蛇兔
        "/world/area/barren_isle/npc/corsair.c": 6,  // 海賊考試海賊
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
    return "/world/area/barren_isle/npc/ka.c";  // 寶箱人卡蒙
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"珍獸們真是抱歉了...我一定要保護好剩餘的珍獸！\n"NOR,
        "$N說道："HIG"非常謝謝$n的幫忙，這些是我的一點心意。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "學習點數 1000 點。\n";
    msg += "銀子 10000 兩。\n";
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
    player->add_point("learn", 1000);
    tell_object(player, HIY"(你獲得了 1000 點學習點數。)\n"NOR);
    player->add("bank", 10000);
    tell_object(player, HIY"(你獲得了 10000 兩銀子。)\n"NOR);
}
