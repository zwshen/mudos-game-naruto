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
    return "鐵塊剛化";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "鐵塊是抵擋傷害的特殊技，能讓身體變如鐵一樣堅硬，「鐵塊•剛」\n";
    msg += "就是鐵塊強化防禦部份後所完成的最強防禦技巧。布魯諾要求你去打\n";
    msg += "幾種擁有甲殼的生物以便了解防禦的精髓。\n";

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
    if( player->query("guild") != "piece" ) return 0;
    if( player->query_skill("body gang", 1) ) return 0;
    if( player->query_class() == "work_sea" ) return 0;
    if( player->query_class() == "little_sea" ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sifa_isle/npc/bruno.c";   // 布魯諾
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N低頭沉思.\n"NOR,
        "$N說道："HIG"$n想要學習鐵塊的進階技能嗎...\n"NOR,
        "$N說道："HIG"去了解甲殼生物的防禦能力順便測試實力吧。\n"NOR,
        "$N說道："HIG"如果完成任務我就教$N。\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/whale_island/npc/crab3.c": 5,  // 大螃蟹
        "/world/area/lake/npc/shrimp.c": 3,         // 蝦兵
        "/world/area/lake/npc/shell.c": 2,          // 貝帥
        "/world/area/muye/npc/bturtle.c": 5,        // 大烏龜
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
    return "/world/area/sifa_isle/npc/bruno.c";   // 布魯諾
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N點頭說道："HIG"既然完成任務那就教$n吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIW"鐵塊•剛"NOR"」\n";
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
    player->set_skill("body gang", 2);
    tell_object(player, HIY"(布魯諾把鐵塊剛化的方法傳授給你了)\n"NOR);
}
