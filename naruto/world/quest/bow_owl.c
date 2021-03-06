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
    return "豹族的災禍";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "聽說豹族部落一個提供豹人修練的地方「轟天瀑」最近被一群擁有強\n";
    msg += "大力量的翼王類『蒼之梟』入侵了，據說已經對豹族部落造成了不小\n";
    msg += "的創傷，所以族長豹頭便前來委託希望有外援能夠幫忙。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 45;
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
    if( player->query_level() < 45 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/thorn_pine/npc/head.c";   // 豹頭
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"這些蒼之梟真是太猖狂了。\n"NOR,
        "$N說道："HIG"真不知道該怎麼對付牠們。\n"NOR,
        CYN"$N「唉」的一聲嘆了口氣。\n"NOR,
        "$N說道："HIG"要是有人能幫忙拿回梟之眼，我一定好好報答他。\n"NOR,
        "$N說道："HIG"據說有 50 隻左右在瀑布附近盤旋...\n"NOR,
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
    if( !present("_OWL_EYE_", player) ) return 0;
    return 1;
}

// 完成任務的NPC  (以檔名來識別)
string getRewarder() {
    return "/world/area/thorn_pine/npc/head.c";   // 豹頭
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N看著$n高興的從木椅上跳了起來。\n"NOR,
        "$N說道："HIG"太棒啦！終於也人打贏那群蒼之梟了嗎！？\n"NOR,
        "$N說道："HIG"就算沒有全部趕走也無所謂！\n"NOR,
        "$N說道："HIG"只要有梟之眼就有獎勵！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "給予"HIR"梟之眼"NOR"的獎勵。\n";
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

    item = present("_OWL_EYE_", player);
    i = item->query_amount();

    if( i > 100 ) {
        i = 100;
        item->add_amount(-i);
    } else {
        destruct(item);
    }
    player->add_point("learn", i*1000);
    player->add("bank", i*50000);
    tell_object(player, HIY"(你得到了豹頭給予的 "+i*1000+" 點學習點數)\n"NOR);
    tell_object(player, HIY"(豹頭還額外給了你 "+i*50000+" 兩銀子！)\n"NOR);
    return;
}
