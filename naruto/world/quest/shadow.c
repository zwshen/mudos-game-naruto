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
    return "猴子溫泉";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "鳴人跟著三忍之一的自來也修行忍術也有一段時間了，這次原本預定\n";
    msg += "要到古老森林的溫泉區「取材」但是到達溫泉區時自來也看到了一堆\n";
    msg += "猴子，立刻勃然大怒，不但把鳴人罵了一頓，連修行也不管了，鳴人\n";
    msg += "只好回一樂拉麵店吃拉麵。為了能夠繼續修行忍術，鳴人找你幫忙趕\n";
    msg += "走古老森林的猴子。\n";

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
    if( player->query("guild") != "muye" ) return 0;
    if( player->query_class() == "inferior" ) return 0;
    if( player->query_skill("shadow", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/naruto.c";   // 鳴人
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N滿臉疑惑，連麵都快要泡爛了.\n"NOR,
        "$N說道："HIG"好色仙人說要教我新忍術，怎麼一看到猴子就氣的跑掉了！\n"NOR,
        "$N說道："HIG"$n去幫忙趕走古老森林的猴子吧！\n"NOR,
        "$N說道："HIG"如果好色仙人教我新忍術，我就教$n影分身之術！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/old_forest/npc/monkeyg.c": 20,   // 母猴
        "/world/area/old_forest/npc/monkeyb.c": 15,   // 公猴
        "/world/area/old_forest/npc/monkeys.c": 10,   // 巨猴
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
    return "/world/area/muye/npc/naruto.c";   // 鳴人
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"$n把猴子趕走了嗎！好色仙人！沒有猴子了！\n"NOR,
        CYN"自來也忽然出現在旁邊.\n"NOR,
        "自來也說道："HIG"好吧！那我們馬上過去！\n"NOR,
        "$N說道："HIG"這是影分身術的卷軸，$n好好學吧！我也要去學新忍術了！\n"NOR,
        CYN"$N跟著自來也一起離開了一樂拉麵店.\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIB"影分身術"NOR"」\n";
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
    player->set_skill("shadow", 2);
    tell_object(player, HIY"(你看著鳴人留下的卷軸，將影分身術學會了)\n"NOR);

    // 鳴人消失
    destruct(npc);
}
