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
    return "騙人布絕招";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "騙人布非常自豪的述說他英勇海上戰士的事蹟，「"HIR"蕃茄醬星"NOR"」更是他\n";
    msg += "最拿手的招式之一！而蕃茄醬星最重要的材料─蕃茄最近卻缺的很嚴\n";
    msg += "重！因為草帽海賊團之前陣子才與海軍艦隊接觸，騙人布船長一人獨\n";
    msg += "挑五百人肯定花費了很多的番茄來使用蕃茄醬星。在沒有蕃茄又想學\n";
    msg += "習這招的情況下，騙人布建議你潛入司法島，去買ＣＰ７瓦傑所製作\n";
    msg += "的義大利麵來提煉蕃茄醬。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 15;
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
    if( player->query_skill("ketchup star", 1) ) return 0;
    if( player->query("level") < 15 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/ship/npc/usopp.c";   // 騙人布
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N很得意地 口圭 口合 口合 口合 ∼∼∼地笑了起來。\n"NOR,
        "$N說道："HIG"先前我就是靠這招打敗了五百名海軍士兵呢！\n"NOR,
        "$N說道："HIG"結果現在把蕃茄都用光了！\n"NOR,
        CYN"$N重重地拍了一下腦袋, 似乎想到什麼主意。\n"NOR,
        "$N說道："HIG"司法島上有個ＣＰ７的瓦傑在賣義大利麵。\n"NOR,
        "$N說道："HIG"我們就用那個來提煉蕃茄醬吧！\n"NOR,
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
        "/world/area/sifa_isle/npc/food/spaghetti.c": 30,  // 義大利麵
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
    return "/world/area/ship/npc/usopp.c";   // 騙人布
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"終於拿齊了！如果是$N大爺肯定更快就拿完了！\n"NOR,
        CYN"$N開始調配蕃茄醬...\n\n"NOR,
        "$N說道："HIG"調配好啦！現在告訴$n蕃茄醬星的要義...\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIR"蕃茄醬星"NOR"」\n";
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
    player->set_skill("ketchup star", 2);
    tell_object(player, HIY"(你學會了騙人布絕招...有種被騙的感覺)\n"NOR);
}
