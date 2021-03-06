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
    return "志同道合";
}

// 任務描述
string getDetail() {
    string msg;
        
    msg  = "土人祭師交給你一封用果皮封住的信，不管你用任何方法都沒\n";
    msg += "辦法打開這封信。信上註明：交給蛇族的蛇祭。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 10;
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
    if( player->query("level") < 10 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/old_forest/npc/wizard3.c";  // 土著主祭
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"阿甘拉趴爹...\n"NOR,
        CYN"$N重重地拍了一下腦袋, 似乎想到了什麼主意.\n"NOR,
        "$N對著$n說道："HIG"忘了外來人不會說土語...\n\n"NOR,
        "$N對著$n說道："HIG"$n...有沒有興趣幫我一個忙？\n"NOR,
        "$N對著$n說道："HIG"我有封信想傳給遙遠的另一位祭師。\n"NOR,
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
    return "/world/area/echo/npc/snake02.c";  // 蛇祭
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N正準備攻擊$n...$n馬上拿出土人祭師的信給$N。\n"NOR,
        CYN"$N接過信件後很輕鬆的就打開了。\n"NOR,
        CYN"$N安靜的看著信件....\n\n"NOR,
        "$N抬起頭說道："HIG"原來平常在祭神時會有人的聲音是他在跟我交談...\n"NOR,
        "$N對著$n說道："HIG"千里來此送信辛苦$n了。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習點數 400 點。\n";
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
    player->add_point("learn", 400);
    tell_object(player, HIY"(你獲得了 400 點學習點數。)\n"NOR);
}
