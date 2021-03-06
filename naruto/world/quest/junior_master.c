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
    return "離開的藥師弟";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "藥大師回想起了當年修行時的一位師弟，雖然有張兇惡的面孔，但是\n";
    msg += "卻擁有一個身為醫生的高尚情操，當年師弟為了造福逐漸老化的人們\n";
    msg += "，不遺餘力發展能夠返老還童的神奇丹藥，只是並不受到其他醫者的\n";
    msg += "認同，最後師弟只好離開前往無人之地繼續開發該藥。藥大師想到此\n";
    msg += "處十分感傷，哽咽的說不出話來了，幫他找副能夠緩心的藥吧。\n";

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
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/wizard/npc/piller.c";  // 藥大師
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
     CYN"$N不停地哭哭啼啼....\n"NOR,
        "$N說道："HIG"剛才整理櫃子發現一張三十年前我和師傅師弟們的合照。\n"NOR,
        "$N說道："HIG"當年師弟為了製造返老還童的神藥，被其他的醫者排斥。\n"NOR,
        "$N說道："HIG"因為製造成功想必會造成轟動...居然就用這種方式打壓...\n"NOR,
        "$N說道："HIG"結果師弟為了我們就隱居深山，唉！\n"NOR,
        "$N說道："HIG"突然想到以前的事，居然會這麼的感傷！\n"NOR,
     CYN"$N想到傷心處, 忍不住放聲大哭.\n"NOR
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
        "/world/area/echo/npc/item/noodle2.c": 1,   // 酸辣麵
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
    return "/world/area/wizard/npc/piller.c";  // 藥大師
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
     CYN"$N聞到$n遞上來麵的香味，停止了哭泣拿起筷子吃麵。\n"NOR,
        "$N說道："HIG"這麵味道真是不錯！整個精神都來了！\n"NOR,
     CYN"$N迅速地吃著麵，發出吸哩酥嚕的聲音。\n"NOR,
     CYN"$N將碗中的湯也喝個精光，滿足的打了個飽嗝。\n"NOR,
        "$N說道："HIG"感謝$n的麵！我的精神好多了。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "獲得藥大師師弟的位置。\n";
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
    message_vision("\n$N高興地說道："HIG"像$n這樣的好人，我相信師弟會願意幫助$n的。\n"NOR, npc, player);
    message_vision("$N說道："HIG"$n就去這裡找我師弟吧。\n"NOR, npc, player);
    message_vision(CYN"$N攤開地圖，用手指著"NOR+HIR"「血腥荒野」"NOR+CYN"的山區。\n\n"NOR, npc, player);
    player->set("capsule_pill", 1);
}
