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
    return "紫米正傳";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "丁次最近不知道從哪裡弄來了很多的紫米飯，但是卻一直不知道要\n";
    msg += "怎麼烹煮才會更好吃，後來有次去到刺松林執行任務，在森林中遇\n";
    msg += "到一位名叫石燕士的人告訴他，紫米要搭配刺松林裡面的紫樹樹液\n";
    msg += "，味道才會發揮的出來。於是丁次拼命的在刺松林中尋找紫樹，卻\n";
    msg += "忽略了刺松林的尖刺，結果被刺的滿身是傷無法再去了。\n";

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
    return "/world/area/muye/npc/din.c";   // 丁次
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N「唉」的一聲嘆了口氣。\n"NOR,
        "$N難過地說道："HIG"刺松林的刺真是太麻煩了...\n"NOR,
        "$N難過地說道："HIG"這樣子我要怎麼拿紫樹樹液呢...\n"NOR,
        CYN"$N「唉」的一聲嘆了口氣。\n"NOR,
    });
        
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/thorn_pine/npc/tree.c": 10,  // 刺松林
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/thorn_pine/npc/item/water02.c": 6,   // 紫色樹液
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
        "$N興奮地說道："HIG"紫樹樹液！\n"NOR,
        "$N興奮地說道："HIG"$n真的拿回來給我了！\n"NOR,
        CYN"$N高興的跳起舞來!!!\n\n"NOR,
        "$N對著$n說道："HIG"太高興了都忘記謝謝$n。\n"NOR,
        "$N對著$n說道："HIG"我這裡紫米太多了，就分給$n一些吧！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "一包"HIM"紫米"NOR"。\n";
    msg += "銀子 1000 兩。\n";
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

    item = new("/world/item/purple_rice.c");
    if( item->move(player) )
        tell_object(player, HIY"(你獲得了一包紫米。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(你獲得了一包紫米，但是掉在地上了。)\n"NOR);
    }
    player->add("bank", 1000);
    tell_object(player, HIY"(你獲得了 1000 兩銀子。)\n"NOR);
}
