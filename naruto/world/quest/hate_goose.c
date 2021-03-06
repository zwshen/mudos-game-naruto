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
    return "推動正名運動";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "方糖勁很生氣的叫你去糖勁湖....不對，是天鵝湖殺天鵝，理由是\n";
    msg += "因為天鵝湖是他方糖勁最喜歡的地方....什麼歪理。總之幫忙這種\n";
    msg += "闊少爺，獎勵應該也不少...就...幫幫他吧。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 15;
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
    if( player->query("level") < 15 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/lake/npc/gin.c";  // 方糖勁
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"$n！快過來！有事要$n幫忙！\n"NOR,
        "$N對著$n說道："HIG"糖勁湖那裡有很多天鵝$n知道吧！？\n\n"NOR,
        "$n疑惑地說道："HIG"那裡不是叫天鵝...\n"NOR,
        "$N生氣地大喊："HIG"什麼天鵝湖！$n想氣死我嗎！\n"NOR,
        CYN"$n露出一個[囧]的臉...\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/muye/npc/goose.c": 15,  // 天鵝
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
// 不可數的物品數量只能設定為1, 不然任務會無法執行
mapping getItem() {
    mapping item = ([
        "/world/area/muye/npc/item/plume.c": 20,  // 羽毛
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
    return "/world/area/lake/npc/gin.c";  // 方糖勁
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N像笨蛋一樣的對自己傻笑。\n"NOR,
        "$N興奮地說道："HIG"這下子沒天鵝了吧！\n"NOR,
        "$N興奮地說道："HIG"那裡就叫糖勁湖啦！\n"NOR,
        "$N興奮地說道："HIG"這些獎賞給$n啦！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習點數 500 點。\n";
    msg += "銀子 20000 兩。\n";
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
    player->add_point("learn", 500);
    tell_object(player, HIY"(你獲得了 500 點學習點數。)\n"NOR);
    player->add("bank", 20000);
    tell_object(player, HIY"(你獲得了 20000 兩銀子。)\n\n"NOR);
    call_out("say_1", 2, npc);
}
void say_1() {
    message_vision(CYN"遠方突然跑來一位慌張的管家...\n"NOR, this_player());
    message_vision("管家緊張地說道﹕"HIG"主人不好了！天鵝..糖勁湖的天鵝又變多了！\n\n"NOR, this_player());
    call_out("say_2", 2, this_object());
}
void say_2() {
    message_vision("方糖勁大喊﹕"HIG"那剛才那傢伙幫了倒忙阿！快把他抓回來！\n"NOR, this_player());
    message_vision("方糖勁苦思著﹕"HIG"剛才那個人是長什麼樣子...嗯？怎麼忘了？\n\n"NOR, this_player());
    message_vision(CYN"趁這個機會快閃人吧...別管他了。\n"NOR, this_player());
}
