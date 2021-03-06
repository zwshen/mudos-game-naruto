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
    return "群狼亂舞";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "「"YEL"嵐腳•孤狼"NOR"」是一招根據狼的攻擊方式所完成的特殊技巧，能夠讓\n";
    msg += "斬擊以跳躍的方式攻向對手。如果對狼群的行動不夠了解是無法順利\n";
    msg += "的使用出孤狼攻擊，努力的完成賈布拉所給的任務吧。\n";

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
    if( player->query_skill("kick wolf", 1) ) return 0;
    if( player->query_class() == "work_sea" ) return 0;
    if( player->query_class() == "little_sea" ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sifa_isle/npc/jia.c";   // 賈布拉
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N低頭沉思.\n"NOR,
        "$N說道："HIG"哈哈哈哈！對我的孤狼絕招有興趣嗎！\n"NOR,
        "$N說道："HIG"先去找一些狼群研究研究吧！\n"NOR,
        "$N說道："HIG"如果還是沒領悟再回來找我吧！哈哈哈哈！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/wild/npc/wolf.c": 10,     // 狼
        "/world/area/wild/npc/bigwolf.c": 6,   // 大狼
        "/world/area/echo/npc/wolf2.c": 6,     // 山狼
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
    return "/world/area/sifa_isle/npc/jia.c";   // 賈布拉
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"喔！？$n真的跑去殺狼阿！哈哈哈！\n"NOR,
        "$N說道："HIG"光是殺狼怎麼可能學會麻！太天真了！\n"NOR,
        "$N說道："HIG"看在$n這麼有心，就教$n吧！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"YEL"嵐腳•孤狼"NOR"」\n";
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
    player->set_skill("kick wolf", 2);
    tell_object(player, HIY"(你學會孤狼技巧了，但感覺賈布拉似乎還有留一手)\n"NOR);
}
