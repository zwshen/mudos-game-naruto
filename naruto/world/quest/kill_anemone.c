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
    return "巨型海葵";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "居住在大海中的魚公魚婆夫妻，原本每天都過著清除多餘珊瑚並從中\n";
    msg += "得到食物的快樂生活，但是因為司法島興建後正義之門改變了四周的\n";
    msg += "海流，導致原本的珊瑚區居然跑出很多的巨型海葵，這些海葵也以珊\n";
    msg += "瑚為食物，但是體型巨大食量更加驚人，跟海葵搶食物的魚公夫妻漸\n";
    msg += "漸支撐不住，已經快要被移居的大型海葵打敗了，所幸這次遇到了你\n";
    msg += "，幫助他們清除海葵吧！\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 30;
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
    if( player->query("level") < 30 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/benthal/npc/father.c";   // 魚公
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"北邊的怪異海流$n應該有見識過吧？\n"NOR,
        "$N說道："HIG"都是那個正義之門改變海流的結果！\n"NOR,
        "$N說道："HIG"還引來了一大堆的巨型海葵...害的我們夫婦三餐都快沒著落了...\n"NOR,
        "$N說道："HIG"$n能幫忙我消滅那些海葵嗎？\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/benthal/npc/anemone.c": 200,  // 巨型海葵
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/benthal/npc/item/root.c": 80, // 葵根
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
    return "/world/area/benthal/npc/father.c";   // 魚公
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N高興的拍手叫好！\n"NOR,
        "$N對著$n說道："HIG"沒想到$n幫我消滅這麼多的海葵！\n"NOR,
        "$N對著$n說道："HIG"為了報答$n，我就將海葵的根部編成盔甲送給$n吧！\n\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "一件"HIG"海葵"NOR+GRN"編成鎧"NOR"\n";
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

    item = new("/world/area/benthal/npc/eq/root_armor.c");
    if( item->move(player) )
        tell_object(player, HIY"(你獲得了一件海葵編成鎧。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(你獲得了一件海葵編成鎧，但是掉在地上了。)\n"NOR);
    }
}
