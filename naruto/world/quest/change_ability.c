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
    return "兔兔裝";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "受到婦女們歡迎的明星克萊門斯，這次又想走可愛的路線，他打算跟\n";
    msg += "其他四位空中飛人一起穿上兔耳朵與兔尾巴在空中表演，這樣不但能\n";
    msg += "吸引婦女同時也能吸引小孩，不過馬戲團裡的兔耳朵跟兔尾巴前些日\n";
    msg += "子才被跳火圈的新人小丑燒個精光，只好麻煩你去找了。\n";

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
    if( player->query("guild") != "hunter" ) return 0;
    if( player->query_class() == "hxh_initial" ) return 0;
    if( player->query_skill("change ability", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/magic_house/npc/clemens.c";   // 克萊門斯
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"怎麼辦阿！臨時需要兔耳朵和兔尾巴卻被燒光了！\n"NOR,
        "$N說道："HIG"$n如果能幫我找來五對！我就教$n轉移魂魄提升能力的技巧！\n"NOR,
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
        "/world/area/whale_island/npc/eq/rears.c": 5,  // 兔耳朵
        "/world/area/whale_island/npc/eq/rtail.c": 5,  // 兔尾巴
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
    return "/world/area/magic_house/npc/clemens.c";   // 克萊門斯
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"找完了嗎！快給我！\n"NOR,
        "$N說道："HIG"呼，總算是趕在表演前將道具拿到手了。\n"NOR,
        "$N說道："HIG"既然說好的就不能食言，好好學著吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIW"魂體轉換"NOR"」\n";
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
    player->set_skill("change ability", 2);
    tell_object(player, HIY"(克萊門斯急急忙忙的教導你，好像漏掉了什麼...)\n"NOR);
}
