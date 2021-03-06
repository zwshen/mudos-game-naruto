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
    return "挑戰極限";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "藍迪強森指定你去猿山連合軍的海賊船上打敗三隻砲擊手後回來向他\n";
    msg += "報告，一來可以測試實力，二來可以看看砲擊手的攻擊方式學習學習\n";
    msg += "在遇到強大反衝擊力時應該怎麼樣去為自己防護，結束後回來向藍迪\n";
    msg += "強森告知經歷，相信他很樂意把技能教給你的。\n";

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
    if( player->query_skill("destory fist", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/magic_house/npc/johnson.c";   // 藍迪強森
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"$n的身體似乎挺強壯的！\n"NOR,
        "$N說道："HIG"不過光是這樣還不夠！\n"NOR,
        "$N說道："HIG"去大海上的猿山連合軍船打敗三位砲擊手讓我瞧瞧！\n"NOR,
        "$N說道："HIG"不但能夠測試實力還能為海軍除害！一舉兩得！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/ship/npc/mob3.c": 3,     // 砲擊手
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
    return "/world/area/magic_house/npc/johnson.c";   // 藍迪強森
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"$n做的不錯阿！\n"NOR,
        "$N說道："HIG"看來這套破壞拳最適合$n了。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIM"破壞拳"NOR"」\n";
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
    player->set_skill("destory fist", 2);
    tell_object(player, HIY"(藍迪強森將破壞拳的基礎教給了你)\n"NOR);
}
