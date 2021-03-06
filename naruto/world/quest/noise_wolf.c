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
    return "不得安寧";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "王百萬終於還是自己去咆哮墓林找老張了，不過在沒找著的情況下\n";
    msg += "在那裡住了一晚，卻被墓林附近的特有大型狼「山狼」所煩擾，因\n";
    msg += "為山狼比一般的狼更會叫而且叫的更大聲，為此被吵到睡眠不足的\n";
    msg += "王百萬決定討回公道。\n";

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
    return "/world/area/echo/npc/wang.c";   // 王百萬
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N臉上青一塊紫一塊!好像非常生氣!\n"NOR,
        "$N生氣地說道："HIG"之前親自去咆哮墓林找老張，晚上被那些山狼吵的睡不著！\n"NOR,
        "$N生氣地說道："HIG"那些山狼真是太可惡了！\n"NOR,
        "$N盯著$n看﹐不知道打些什麼主意。\n"NOR,
        "$N對著$n說道："HIG"幫我去教訓一下那些山狼吧！\n"NOR,
        "$N生氣地說道："HIG"除了帶回牠們的毛皮，我還要看到牠們特有的長牙齒！\n"NOR,
    });
        
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/echo/npc/wolf1.c": 10,    // 幼山狼
        "/world/area/echo/npc/wolf2.c": 20,    // 山狼
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/echo/npc/item/tooth.c": 10,  // 狼牙
        "/world/area/wild/npc/eq/wolf_fur.c": 5,  // 狼皮
        "/world/area/wild/npc/eq/wolf_tail.c": 2, // 狼尾
        "/world/area/wild/npc/wp/wolf_claw.c": 1, // 狼爪
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
    return "/world/area/echo/npc/wang.c";   // 王百萬
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N興奮地說道："HIG"沒錯沒錯！就是這種牙齒！\n"NOR,
        "$N說道："HIG"想之前去的時候看到還覺得真恐怖！\n"NOR,
        "$N對著$n說道："HIG"現在覺得也沒什麼麻！這都是$n的功勞阿！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "學習點數 500 點。\n";
    msg += "銀子 30000 兩。\n";
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
    player->add("bank", 30000);
    tell_object(player, HIY"(你獲得了 30000 兩銀子。)\n"NOR);
}
