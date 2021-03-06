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
    return "冰鎮甜粥";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "藥大師偶然間得到的一個方子，上面所寫的居然是失傳已久的藥粥\n";
    msg += "『冰鎮甜粥』！不過這藥粥的材料非常的奇怪，都需要一些特別的\n";
    msg += "食材，不過藥大師說他也試著用一般食材去製作過，結果就只是普\n";
    msg += "通的粥而已，所以他也在懷疑這個方子的可信程度。\n";
    msg += "藥大師也曾經試著尋找過這些特別材料，但是都無功而返，只好麻\n";
    msg += "煩你去幫忙他收集了！\n";
    msg += "紫米在各個商店都一粒難求，因為聽說全都被秋道家給收購了！\n";
    msg += "黃金紅豆是御手洗紅豆的家傳秘材，相信找他應該會有結果。\n";
    msg += "煙燻綠豆是鯨魚島老婆婆的拿手小菜，但是她年事已高...\n";
    msg += "落花生目前時節不對，但是曾經有人看到天鵝湖的商人在吃。\n";
    msg += "桂圓乾是回音山洞旁邊村子的名產，但是被蛇人毀壞無人居住...\n";
    msg += "甜湯在鯨魚島燒賣店可是很出名的產品喔！只要有心都買的到！\n";

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
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/wizard/npc/piller.c";   // 藥大師
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"最近我得到了一個神奇的秘方。\n"NOR,
        "$N說道："HIG"只要能夠調配出來，應該比目前所賣的藥品都要有效吧！\n"NOR,
        "$N說道："HIG"不過材料非常特別，連我都不知道要上哪去找。\n"NOR,
        "$N說道："HIG"如果$n有這些材料我到是能幫忙調製。\n"NOR,
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
        "/world/item/purple_rice.c": 1,                        // 紫米
        "/world/item/gold_adzuki.c": 1,                        // 黃金紅豆
        "/world/item/smoke_mung.c": 1,                         // 煙燻綠豆
        "/world/item/peanut.c": 1,                             // 落花生
        "/world/item/longan.c": 1,                             // 桂圓乾
        "/world/area/whale_island/npc/food/sweet_broth.c": 10, // 甜湯
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
    return "/world/area/wizard/npc/piller.c";   // 藥大師
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N拍拍$n的肩膀，說道:好小子 有前途喔！！\n"NOR,
        "$N對著$n說道："HIG"沒想到$n還真的把材料弄來了！\n"NOR,
        "$N對著$n說道："HIG"接下來就交給我吧！\n\n"NOR,
        CYN"$N將材料丟進大鍋中用大火熬煮。\n"NOR,
        CYN"只見鍋中噴出五彩煙霧，令人目不轉睛的看著。\n\n"NOR,
        CYN"忽然$N拿出一個大盆，裡面裝滿了冰塊。\n"NOR,
        CYN"$N將大盆放到鍋中，發出沙沙的聲音。\n\n"NOR,
        CYN"直到盆中冰塊化為水後，$N便將水倒掉換上新的冰塊。\n\n"NOR,
        "$N高興地說道："HIG"煮了一大鍋呢！不知道能裝幾碗！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "數碗"HIC"冰鎮"HIY"甜粥"NOR"。\n";
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
    int amount;
    object item;

    amount = random(3) + 1;    // 設定可能得到的物品數量為1-4
    item = new("/world/drug/ice_heal.c");

    item->set_amount(amount);  // 加入數量

    if( item->move(player) )
        tell_object(player, HIY"(藥大師裝了 "HIG+amount+HIY" 碗冰鎮甜粥交給你。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(藥大師裝了 "HIG+amount+HIY" 碗冰鎮甜粥交給你，但是掉在地上了。)\n"NOR);
    }
    npc->set_amount(0);
}
