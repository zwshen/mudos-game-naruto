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
    return "蟹黃生蠔鮑魚龜頭水果拉麵";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "名字有夠長的怪異拉麵，不過聽說味道好像不錯，如果對這道奇特\n";
    msg += "料理有興趣的話，就照拉麵店師傅的要求去搜集物品吧。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 5;
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
    if( player->query("level") < 5 ) return 0;
    if( player->query("bank") < 30000 ) return 0;
    if( !player->query_temp("muscle_tank") ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/fooder.c";   // 拉麵店老闆
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"$n只要帶來十個蟹黃、五隻生蠔、十顆鮑魚、二個龜頭跟五個水果王來給我...\n"NOR,
        "$N說道："HIG"再付個三萬兩銀子。\n"NOR,
        "$N說道："HIG"我便會幫$n煮「蟹黃生蠔鮑魚龜頭水果拉麵」。\n"NOR,
        "$N邪惡地說道："HIG"要是等我收到材料又發現$n的錢不夠...材料我就直接沒收了。\n"NOR,
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
        "/world/area/whale_island/npc/food/crab_roe.c": 10,   // 蟹黃
        "/world/item/fish6.c": 10,                            // 鮑魚
        "/world/area/lake/npc/item/oyster.c": 5,              // 生蠔
        "/world/area/old_forest/npc/item/fruit4.c": 5,        // 水果王
        "/world/area/muye/npc/item/turtle_head.c": 2,         // 龜頭
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
    return "/world/area/muye/npc/fooder.c";   // 拉麵店老闆
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N點了點頭。\n"NOR,
        "$N說道："HIG"現在就來製作拉麵吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "一碗蟹黃生蠔鮑魚龜頭水果拉麵。\n";
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
    object item;

    item = new("/world/area/muye/npc/item/noodle.c");
    if( player->query("bank") < 30000 ) {
        message_vision("$N邪笑著道："HIG"$n的錢不夠阿！東西我沒收了！麵也不給$n！\n"NOR, npc, player);
        return;
    }
    player->add("bank", -30000);
    if( item->move(player) )
        tell_object(player, HIY"(你獲得了一碗蟹黃生蠔鮑魚龜頭水果拉麵。)\n"NOR);
    else {
        if( environment(player)->is_area() ) move_side(item, player);
        else item->move(environment(player));
        tell_object(player, HIY"(你獲得了一碗蟹黃生蠔鮑魚龜頭水果拉麵，但是掉在地上了。)\n"NOR);
    }
}
