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
    return "金珠報喜";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "方氏企業老闆委託的重要任務！任務目標是方家最近才買進的新\n";
    msg += "寶物，金珠！不過都被偷了上哪去找呢，隨便拿幾顆巨大珍珠交\n";
    msg += "差了事就好了。\n";

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
    return "/world/area/lake/npc/gin.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N高傲地說道："HIG"身為大企業方家！家裡怎麼能沒點吉祥物呢！\n"NOR,
        "$N高傲地說道："HIG"你看看！金元寶...金魚池...金石堂....應有盡有阿！\n"NOR,
        CYN"$N慘叫一聲, 滿臉「那也安捏?!?!?」的表情.\n"NOR,
        "$N驚慌地說道："HIG"昨天買的金珠怎麼不見了！\n"NOR,
        "$N瞪著$n說道："HIG"你你你叫啥名字！快去幫我找金珠！\n"NOR,
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
        "/world/area/lake/npc/item/pearl.c": 10,  // 巨大珍珠
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
    return "/world/area/lake/npc/gin.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"拿來了嗎？怎麼不是金珠呢！\n"NOR,
        CYN"$N低頭沉思.\n"NOR,
        "$N說道："HIG"這些看起來好像也不錯！\n"NOR,
        "$N對著$n說道："HIG"既然東西找到了當然要給點獎勵啦！\n"NOR,
        "$N對著$n說道："HIG"身為大老闆出手也要闊氣些！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "銀子 60000 兩。\n";
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
    player->add("bank", 60000);
    tell_object(player, HIY"(你獲得了 60000 兩銀子。)\n"NOR);
}
