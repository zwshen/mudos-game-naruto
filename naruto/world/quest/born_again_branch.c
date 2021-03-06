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
    return "危險沼澤地";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "松�竣j輔因為能和樹說話而與樹產生了深厚的友情，聽說在戰事林的\n";
    msg += "附近有一片名為「絕望沼澤」地方，裡面有種名叫沼澤毒魚的生物會\n";
    msg += "將樹木腐蝕，絕望沼澤原本大半的地段似乎都是森林，但是目前已經\n";
    msg += "便成如此了，因此松�竣j輔要求你去清除一些毒魚。\n";

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
    if( player->query_skill("born-again branch", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/magic_house/npc/daisuke.c";   // 松�竣j輔
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"$n知道戰事林的林地為什麼愈來愈小了嗎！\n"NOR,
        "$N說道："HIG"因為上方絕望沼澤裡有種毒魚會腐蝕樹木！\n"NOR,
        "$N說道："HIG"如果有人能去料理牠們我就把樹木重生之術教他！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/bone/npc/fish.c": 10,     // 沼澤毒魚
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
    return "/world/area/magic_house/npc/daisuke.c";   // 松�竣j輔
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"沒想到$n真的去殺了阿！\n"NOR,
        "$N說道："HIG"雖然牠們繁殖的很快，不過我相信會有幫助的。\n"NOR,
        "$N說道："HIG"當初約定的技能這就來教$n吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIY"樹枝重生"NOR"」\n";
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
    player->set_skill("born-again branch", 2);
    tell_object(player, HIY"(你聽了松�竣j輔的指導，似乎有些心得了)\n"NOR);
}
