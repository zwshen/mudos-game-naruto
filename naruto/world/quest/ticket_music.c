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
    return "支援音忍";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "音鮮正為了大蛇丸所派下的任務而感到頭痛，你稍微過目一下清單\n";
    msg += "後也嚇了一跳，那麼多的東西打算在幾天內就搜集完畢，簡直是不\n";
    msg += "可能的任務。看到音鮮那愁眉苦臉的樣子就幫幫他吧，「也許」他\n";
    msg += "會報答你吧...\n";

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
    if( player->query("guild") != "hunter" ) return 0;
    if( player->query_class() == "hxh_initial" ) return 0;
    if( player->query_skill("lending ticket") < 20 ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sneakhole/npc/san.c";   // 音鮮
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N「唉」的一聲嘆了口氣。\n"NOR,
        "$N說道："HIG"大蛇丸大人怎麼搞的...一次派這麼多任務下來...\n"NOR,
        "$N說道："HIG"光我一個人怎麼處理的完！\n"NOR,
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
        "/world/area/wild/npc/item/snake_skin.c": 30,   // 蛇皮
        "/world/area/wild/npc/item/snake_egg.c": 30,    // 蛇蛋
        "/world/area/wild/npc/item/snake_gall.c": 30,   // 蛇膽
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
    return "/world/area/sneakhole/npc/san.c";   // 音鮮
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N快樂的手舞足蹈!!!\n"NOR,
        "$N對著$n說道："HIG"這樣我又能減少一些負擔了！\n"NOR,
        "$N對著$n說道："HIG"謝謝$n！我欠$n個人情！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "好像沒什麼獎勵...\n";
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

    item = new("/daemon/skill/hxh/special/obj/music_ticket.c");
    if( item->move(player) )
        tell_object(player, HIY"(因為音鮮欠了你人情，因此你得到一張借貸券。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(因為音鮮欠了你人情，因此你得到一張借貸券，但是掉在地上了。)\n"NOR);
    }
}
