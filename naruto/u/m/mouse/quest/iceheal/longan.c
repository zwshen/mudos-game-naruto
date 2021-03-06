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
    return "伸張正義";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "經由堂秋得知原來咆哮墓林原本是一個村莊，因為村中盛產桂圓而\n";
    msg += "在每年桂圓量產季都有吃桂圓的大型活動，結果某次活動時附近剛\n";
    msg += "好有與族人分離的蛇族遺民，牠們聞到桂圓香之後才大舉攻入村子\n";
    msg += "村子因此被破壞殆盡...\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 25;
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
    if( player->query("level") < 25 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/echo/npc/chu.c";   // 堂秋
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N拿著火槍說道："HIG"這些可惡的蛇人，我一定不會放過牠們！\n"NOR,
        CYN"$n上前詢問事情的經過...\n\n"NOR,
        "$N說道："HIG"這裡原本是個美麗的山中村子，專門種植桂圓。\n"NOR,
        "$N說道："HIG"每年還為了桂圓舉辦節日！我們都稱為桂節。\n"NOR,
        "$N難過地說道："HIG"誰知道有次桂節的時候因為煮桂圓的香味。\n"NOR,
        "$N難過地說道："HIG"居然引來了一堆蛇人...村子也就這樣沒了...\n"NOR,
        CYN"$N「唉」的一聲嘆了口氣。\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/echo/npc/snake03.c": 15,  // 蛇人
        "/world/area/echo/npc/snake01.c": 1,   // 蛇守
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/wild/npc/item/snake_skin.c": 10,   // 蛇皮
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
    return "/world/area/echo/npc/chu.c";   // 堂秋
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N瞠目結舌，好像看到了一件不可思議的事。\n"NOR,
        "$N對著$n說道："HIG"$n居然殺死了這麼多的蛇人！\n"NOR,
        "$N對著$n說道："HIG"還將他們的頭目蛇守也殺死了！\n"NOR,
        CYN"$N低頭沉思.\n\n"NOR,
        "$N慚愧地對$n說道："HIG"我也沒什麼東西能送給$n...就給些桂圓乾好了！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "一袋"HIW"桂圓乾"NOR"。\n";
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

    item = new("/world/item/longan.c");
    if( item->move(player) )
        tell_object(player, HIY"(你獲得了一袋桂圓乾。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(你獲得了一袋桂圓乾，但是掉在地上了。)\n"NOR);
    }
}
