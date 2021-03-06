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
    return "偷菜作戰";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "秋道一族的家傳秘藥，正是秋道家族百年不衰的重要物件之一。秋道\n";
    msg += "家新一代成員秋道丁次，最近正在煩惱製作秘藥的材料不夠了，正好\n";
    msg += "碰上你想學習這個招式，便要求你去獸爪荒野北邊的鄉野農村偷菜。\n";
    msg += "偷到丁次要求的數量後拿回來給丁次就可以了。\n";

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
    if( player->query_skill("akimichi pill", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/din.c";   // 丁次
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N低頭沉思.\n"NOR,
        "$N吃著零食說道："HIG"$n想學秋道秘藥？那正好！\n"NOR,
        "$N吃著零食說道："HIG"$n去獸爪荒野北邊的「鄉野農村」幫我偷拔一些菜回來。\n"NOR,
        "$N吃著零食說道："HIG"拿回來我就教$n技能！記住不能被阿斯瑪老師知道喔！\n"NOR,
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
        "/world/area/rural_area/item/pill_obj01.c": 10,   // 菠菜
        "/world/area/rural_area/item/pill_obj02.c": 10,   // 紅蘿蔔
        "/world/area/rural_area/item/pill_obj03.c": 10,   // 小辣椒
        "/world/area/rural_area/item/pill_obj04.c": 10,   // 芹菜
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
    return "/world/area/muye/npc/din.c";   // 丁次
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N吃著零食說道："HIG"都偷回來了，那就稍微告訴$n一些秋道秘藥的知識吧...\n"NOR,
        CYN"$N滿嘴零食的為$n解說秋道秘藥...\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIR"秋道秘藥"NOR"」\n";
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
    player->set_skill("akimichi pill", 2);
    tell_object(player, HIY"(經過丁次的指導後，你大概知道秘藥的成份了)\n"NOR);
}
