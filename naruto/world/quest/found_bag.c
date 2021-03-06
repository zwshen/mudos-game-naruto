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
    return "有機材料";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "鐵器老闆為了製作能夠促進農作物生長的工具，嘗試在材料包中加\n";
    msg += "入一些有機農作物當做合成物。不過最近鋪裡收了很多的學徒使他\n";
    msg += "無法抽身前去採集物資，所以將任務委託給你幫忙他收集一些必要\n";
    msg += "的材料，希望他的構想會成功！\n";

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
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/iron.c";   // 鐵器老闆
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"能幫我一個忙嗎？\n"NOR,
        "$N對著$n說道："HIG"我需要一些蔬果進行創新合成技術。\n"NOR,
        "$N皺眉說道："HIG"但是學徒太多讓我離不開這裡。\n"NOR,
        CYN"$N用力拍了$n一下大聲喊著：「$n！就決定是你了！」\n"NOR,
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
        "/world/area/rural_area/item/pill_obj03.c": 10, // 芹菜
        "/world/area/rural_area/item/pill_obj02.c": 10, // 紅蘿蔔
        "/world/area/rural_area/item/pill_obj01.c": 5,  // 菠菜
        "/world/drug/mpill4.c": 5,                      // 超大菊花茶
        "/world/item/longan.c": 1,                      // 桂圓乾
        "/world/item/gold_adzuki.c": 1,                 // 黃金紅豆
        "/world/area/rural_area/npc/item/wafer.c": 8,   // 糯米
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
    return "/world/area/muye/npc/iron.c";   // 鐵器老闆
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N露出一臉「我果然沒看錯人」的表情。\n"NOR,
        "$N對著$n說道："HIG"我覺得$n更適合當我的學徒呢！\n"NOR,
        "$N對著$n說道："HIG"這包材料包就送給$n吧！\n"NOR,
        CYN"$N愉快地笑著。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "一包材料包。\n";
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

    item = new("/world/area/old_forest/item/bag.c");
    if( item->move(player) )
        tell_object(player, HIY"(鐵器老闆的材料包順利交給你了。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(因為身上太重，鐵器老闆的材料包掉到地上了。)\n"NOR);
    }
}
