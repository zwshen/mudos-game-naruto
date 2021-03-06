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
    return "戰鬥教學";
}

// 任務描述
string getDetail() {
    string msg;
        
    msg  = "這位可面生得很啊，肯定是新來的。\n\n";
    msg += "當出外攻擊 Mob 時可以使用指令向 Mob 討較(help kill, help fight)\n";
    msg += "如果不小心受到傷害，記得先設好自動逃跑以防萬一阿！(help wimpy)\n\n";
    msg += "總之先到天上人間的地圖上尋找"HIR"♀"NOR"記號吧！\n";
    msg += "如果發現野狗就對牠發動攻擊！在殺死牠之後記得撿屍體喔！(help get)\n\n";
    msg += "前面的事件都完成後，試著尋找武大師吧！\n";
    msg += "相信他會很樂意提供武器給你，幫助你順利成長的！\n";

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
    return "/world/area/wizard/npc/chi.c";
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"這位可面生得很啊，肯定是新來的。\n"NOR,
        "$N對著$n說道："HIG"這個任務是教你如何在世界中戰鬥的。\n"NOR,
        "$N對著$n說道："HIG"決定接這個任務就按 "HIY"y"HIG" 吧！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/npc/dog.c": 1,  // 野狗
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
    return "/world/area/wizard/npc/wper.c";
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"$n就是易口癡介紹來的新手吧！\n"NOR,
        "$N對著$n說道："HIG"這把新生戰刀$n就帶上吧！雖然不是什麼好武器。\n"NOR,
        "$N對著$n說道："HIG"裝備武器可以選擇左手、右手和雙手！(help wield)\n"NOR,
        "$N對著$n說道："HIG"武器必須裝備之後才能觀看能力值(help identify)。\n"NOR,
        "$N對著$n說道："HIG"或是使用 query 功能也能查看到各種的物品喔！(help query)\n"NOR,
        "$N對著$n說道："HIG"話不多說！讓$n自己嘗試吧！\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = "一把新生戰刀。\n";
    return msg;
}
/*
    任務獎勵
    獎勵應該能自由發揮，如：
        1. 獲得經驗
        2. 獲得物品
        3. 獲得短暫Buff
        4. 習得某技能
        5. 更改玩家狀態, ex: 轉職
*/
void reward(object player, object npc) {
    object wp;

    wp = new("/world/wp/newblade.c");
    if( wp->move(player) )
        tell_object(player, HIY"(你獲得了一把新生戰刀。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把wp移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(wp, player);
        // 如果是在 room 中，把wp移到player所處的房間中
        else wp->move(environment(player));
        tell_object(player, HIY"(你獲得了一把新生戰刀，但是掉在地上了。)\n"NOR);
    }
}
