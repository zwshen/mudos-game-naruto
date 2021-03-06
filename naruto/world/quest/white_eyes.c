#include <ansi.h>

void create() { seteuid(getuid()); }

// 說明此檔是任務，這個函式不需要變動
int isQuest() { return 1; }

/* 此任務是否能重複解  return 0  不能重複
                       return 1  可重複
   建議最好設定不能重複。
 */
int isNewly() { return 1; }

// 任務名稱
string getName() {
    return "最後心願";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "日向奅暉與其他日向家族的人受命前去音忍領地音隱密道查探，但是\n";
    msg += "在半路上被音之下忍所偷襲，只有奅暉身受重傷逃了回來，雖然經過\n";
    msg += "童角的治療，卻仍然活不過明日，因此他拜託你幫忙報這個仇，了了\n";
    msg += "他有生以來最後的心願。\n";

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
    if( player->query("guild") != "muye" ) return 0;
    if( player->query_class() == "inferior" ) return 0;
    if( player->query_skill("white eyes", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/white_eyes_ninja.c";   // 日向奅暉
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N氣憤地說道："HIG"可惡的音之忍者...居然偷襲我們...\n"NOR,
        "$N難過地說道："HIG"都怪我太不爭氣！沒有發現他們的埋伏！\n"NOR,
        "$N抓住$n說道："HIG"$n能幫我報這個仇嗎！\n"NOR,
        "$N說道："HIG"只要了了這個心願，我可以將剩下的生命都交給$n。\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/sneakhole/npc/ninja04.c": 15,      // 音隱忍者
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
    return "/world/area/muye/npc/white_eyes_ninja.c";   // 日向奅暉
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N振奮地說道："HIG"殺死他們了？！太好了...太好了！\n"NOR,
        CYN"$N太過激動，吐出了一口鮮血...\n"NOR,
        "$N說道："HIG"...看來我也活不久了。\n"NOR,
        "$N抓著$n說道："HIG"我決定將我剩餘的左眼交給$n。\n"NOR,
        "$N說道："HIG"我們日向一族的白眼$n應該聽說過吧，好好運用吧...\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "獲得日向奅暉的生命？\n";
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
    player->set_skill("white eyes", 2);
    tell_object(player, HIY"(童角將奅暉的左眼移植給了你，你獲得日向家的血繼限界了)\n"NOR);
    npc->die();

    destruct(npc);
}
