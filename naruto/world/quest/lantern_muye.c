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
    return "怪物的燈籠";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "一種棲息在戰事林綠色怪物所拿的燈籠，據說那燈籠擁有治療傷害的\n";
    msg += "神奇效果，連大蛇丸都很想得到它。因此木葉村對這個任務非常的重\n";
    msg += "視，更提高了獎勵吸引木葉村以外的人幫忙。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 35;
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
    if( player->query_level() < 35 ) return 0;
    if( player->query("quest/lantern") ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/bone/npc/gau.c";   // 童角
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"所謂的燈籠就是生活在戰事林一群綠色怪物通倍利拿的燈籠。\n"NOR,
        "$N說道："HIG"擁有治療的功能，所以大蛇丸一直在尋找。\n"NOR,
        "$N說道："HIG"如果有拿到燈籠請交給我們木葉村。\n"NOR,
        "$N說道："HIG"千萬不能讓他們成功了解燈籠的構造！\n"NOR,
        "$N說道："HIG"只要能拿來 100 盞...我想應該就差不多了。\n"NOR,
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
    if( !present("_TONBELI_A_", player) ) return 0;
    if( player->query("quest/lantern") ) return 0;
    return 1;
}

// 完成任務的NPC  (以檔名來識別)
string getRewarder() {
    return "/world/area/bone/npc/gau.c";   // 童角
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"嗯，非常感謝$n的幫忙！\n"NOR,
        "$N說道："HIG"如果因此事讓大蛇丸的雙手無法恢復，三代大人在天之靈也會感到欣慰的！\n"NOR,
        "$N說道："HIG"依照約定，將付給$n一百盞以內的燈籠獎勵！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "給予"HIG"通倍利燈籠"NOR"的獎勵。\n";
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
    int i;

    item = present("_TONBELI_A_", player);
    i = item->query_amount();

    if( i > 100 ) {
        i = 100;
        item->add_amount(-i);
    } else {
        destruct(item);
    }
    // 用系統去掃所有任務檔找是否完成比較吃資源
    // 直接這樣加個永久的 quest 編號以後也方便使用
    player->set("quest/lantern", 1);
    player->add_point("learn", i*500);
    tell_object(player, HIY"(你得到了童角給予的 "+i*500+" 點學習點數)\n"NOR);
    return;
}
