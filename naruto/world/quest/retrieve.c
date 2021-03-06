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
    return "廢棄物回收";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "按豹昲的說法，他是專門回收合成時殘留雜物的回收家，雖然其他\n";
    msg += "東西原本也可以找他回收，不過他不想花費功夫去做大家都能做的\n";
    msg += "事。所以有合成殘留物要回收時再找他吧。\n\n";
    msg += "任務需求：\n";
    msg += "    銀子 ? 兩。\n";
    msg += "    合成後的廢棄物。\n";

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
    return "/world/area/thorn_pine/npc/fee.c";   // 豹昲
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N挖著鼻孔說道："HIG"要回收廢棄物喔？\n"NOR,
        CYN"$N滿臉無耐似乎根本不想接這個工作。\n"NOR,
        "$N不爽地說道："HIG"不接沒錢吃飯！算了！\n"NOR,
        "$N對$n大吼："HIG"我只收合成廢棄物！知道了嗎！\n"NOR,
        "$N對$n大吼："HIG"爐渣一沱一百兩銀子！廢油一桶一千兩銀子！\n"NOR,
        "$N隨手點起一根煙說道："HIG"價錢很公道了，不想回收就滾吧。\n"NOR,
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
    return ([]);
}

// 完成任務的條件除了系統提供的
// 1. 搜集物品
// 2. 殺了足夠數量的怪物之外
// 有需要的話，還可以自訂完成任務條件
// return 1, 為滿足條件, return 0;為失敗
int postCondition(object player, object npc)
{
    if( !present("scrap", player) && !present("residue", player) ) return 0;
    return 1;
}

// 完成任務的NPC  (以檔名來識別)
string getRewarder() {
    return "/world/area/thorn_pine/npc/fee.c";   // 豹昲
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N拿起存摺看了一下，$n彷彿看見一道金光閃過...\n"NOR,
        "$N對著$n說道："HIG"好了！剩下的就交給我吧。\n"NOR,
        CYN"想不到$N忽然有如脫胎換骨，三兩下就將廢棄物搬走了。\n\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "清理廢棄物。\n";
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
    int i, j;
    object item;

    if( objectp(item = present("scrap", player)) ) {
        i = item->query_amount();
        j = i*1000;
        tell_object(player, HIY"清除廢油"HIR+chinese_number(item->query_amount())+HIY"桶、"NOR);
        destruct(item);
    } else {
        j = 0;
    }
    if( objectp(item = present("residue", player)) ) {
        i = item->query_amount();
        j += i*100;
        tell_object(player, HIY"清除爐渣"HIM+chinese_number(item->query_amount())+HIY"沱、"NOR);
        destruct(item);
    }
    player->add("bank", -j);
    tell_object(player, HIY"總共收你"HIG+chinese_number(j)+"兩銀子"HIY"。\n\n"NOR);
}
