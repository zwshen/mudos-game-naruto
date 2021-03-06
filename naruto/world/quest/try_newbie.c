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
    return "新手試煉";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "這是新手導師辛心長所給予你的最後任務，目的是幫助你能夠在尚\n";
    msg += "未出頭時有個輕鬆的地方能夠搜集經驗，快去看看這個地方吧！到\n";
    msg += "了目的地之後應該會看到另一位新手導師，就找他完成任務吧。\n";
msg += "該不會忘記地點了吧！？  地點在「"HIY"天上人間"NOR"」東邊「"HIC"精靈之門"NOR"」\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 1;
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
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/wizard/npc/zhang.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"$n找不到練功的地方嗎？\n"NOR,
        "$N說道："HIG"讓我新手導師辛心長推薦$n一個好地方吧！\n"NOR,
        "$N說道："HIG"位置就在從這裡往西(w)走之後的地圖"HIW"[天上人間]"HIG"喔！\n"NOR,
        "$N說道："HIG"可以輸入 map 去找一個叫"HIC"[精靈之門]"HIG"的地方。\n"NOR,
        "$N說道："HIG"如果找不到呢！就往南(s)走，看到[五行傳送]之後往東(e)，就會看到啦！\n"NOR,
        "$N對著$n說道："HIG"加油吧$n！希望$n練功愉快！\n"NOR,
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
    return "/world/area/wizard/npc/fei.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"應該是辛心長叫$n來的吧！\n"NOR,
        "$N對著$n說道："HIG"輸入 "HIY"seedoor"HIG" 後回答由符號拼出的數字，就可以進去了！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "銀子 10 兩。\n";
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
    player->add("bank", 10);
    tell_object(player, HIY"(你獲得了 10 兩銀子。)\n"NOR);
}
