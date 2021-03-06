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
    return "治療大蛇丸";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "一種棲息在戰事林綠色怪物所拿的燈籠，據說那燈籠擁有治療傷害的\n";
    msg += "神奇效果，因此音忍村之首大蛇丸非常想要得到這個燈籠，因為據說\n";
    msg += "之前音隱連合沙隱村進攻木葉，為首的大蛇丸挑戰自己的老師猿飛，\n";
    msg += "雖然獲勝但自己的雙手也被廢去，所以才如此渴望這個燈籠....但是\n";
    msg += "如果你不想死的話....在大蛇丸的領地上可千萬別提此事。\n";

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
    return "/world/area/bone/npc/lon.c";   // 竹取剛之郎
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"喔？想知道幫助大蛇丸大人找燈籠有什麼獎賞？\n"NOR,
        "$N說道："HIG"當然是花不完的金銀財寶。\n"NOR,
        "$N說道："HIG"木葉村那種獎勵型的方式根本就行不通。\n"NOR,
        "$N說道："HIG"這年頭有錢能使鬼推磨阿，哈哈哈！\n"NOR,
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
    return "/world/area/bone/npc/lon.c";   // 竹取剛之郎
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"很好！這樣大蛇丸大人重生之日也不遠了！\n"NOR,
        "$N說道："HIG"就一個為錢賣命的人來說，$n做的很不錯！\n"NOR,
        "$N說道："HIG"這點錢就拿去收好吧。\n"NOR,
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
    player->add("bank", i*30000);
    tell_object(player, HIY"(你得到了竹取剛之郎給予的 "+i*30000+" 元獎勵金)\n"NOR);
    return;
}
