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
    return "隔空抓藥";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "你不小心中了古代土人老巫醫的咒法「寄生丸」不管用盡任何方法\n";
    msg += "也拿不下來，因為聽說張穎擁有隔空抓藥的能力，所以想找她把這\n";
    msg += "討厭的丸子給除掉，沒想到張穎居然要求你先付一筆費用才肯幫忙\n";
    msg += "抓藥...真是趁人之危...\n\n";
    msg += "任務需求：\n";
    msg += "    銀子 100000 兩。\n";

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
    if( !present("_BAD_PILL", player) ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/old_forest/npc/ying.c";   // 張穎
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$n仔細的將所中的巫毒告訴$N...\n"NOR,
        "$N說道："HIG"這麼簡單的事情找我就對了，隔空抓藥可是我的強項！\n"NOR,
        CYN"$N臉上露出一抹詭異的笑容。\n"NOR,
        "$N說道："HIG"那就拿個十萬兩銀子過來吧！\n"NOR,
        CYN"$n慘叫一聲, 滿臉「那也安捏?!?!?」的表情.\n"NOR,
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
    if( player->query("bank") < 100000 ) return 0;
    return 1;
}

// 完成任務的NPC  (以檔名來識別)
string getRewarder() {
    return "/world/area/old_forest/npc/ying.c";   // 張穎
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N看著銀行裡的存款金額點了點頭。\n"NOR,
        "$N對著$n說道："HIG"看我表演吧！\n"NOR,
        CYN"$N微微皺起了眉頭，兩手手掌高舉向天。\n"NOR,
        CYN"只見$N手掌朝後一翻，$n頓時感到身上一陣刺痛。\n"NOR,
        CYN"那寄生丸已經被$N給除下了。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "去除寄生丸。\n";
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
    object item;

    item = present("_BAD_PILL", player);
    player->add("bank", -100000);
    tell_object(player, HIY"(張穎成功的把藥除掉了，你感到身子輕鬆不少)\n"NOR);
    destruct(item);
}
