#include <ansi.h>

// 說明此檔是任務，這個函式不需要變動
int isQuest() { return 1; }

/* 此任務是否能重複解  return 0  不能重複
                       return 1  可重複
   建議最好設定不能重複。
 */
void create() { seteuid(getuid()); }

int isNewly() { return 0; }

// 任務名稱
string getName() {
    return "甲殼搜集";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "開著拉麵店的老闆，想要為店內的牆壁上做一些裝飾，能夠放的\n";
    msg += "很久又不會損壞，而且外型美觀的物品，老闆第一個想到的物品\n";
    msg += "就是生物們的外殼，好看又堅硬耐撞。\n";
    msg += "拉麵店裡面的客人提供給你的甲殼位置清單：\n";
    msg += "天鵝湖─龜甲。\n";
    msg += "天鵝湖底─蝦殼、蟹殼、貝殼。\n";
    msg += "古老森林─椰子殼。\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 12;
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
    if( player->query("level") < 12 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/muye/npc/fooder.c";  // 拉麵店老闆
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N低頭沉思.\n"NOR,
        "$N尋問著客人："HIG"店面的裝潢好像有點單調...該怎麼改善呢？\n\n"NOR,
        CYN"客人們七嘴八舌的討論著...\n"NOR,
        "$N恍然大悟地說道："HIG"果然還是甲殼類的東西掛上最好看阿！\n"NOR,
        "$N尋問著客人："HIG"有人能幫我挑選一些甲殼嗎？\n"NOR,
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
        "/world/area/lake/npc/eq/shrimp.c": 4,     // 蝦殼
        "/world/area/lake/npc/eq/crab.c": 4,       // 蟹殼
        "/world/area/lake/npc/eq/shell.c": 4,      // 貝殼
        "/world/eq/armor/turtle.c": 1,             // 龜甲
        "/world/area/old_forest/npc/eq/coco.c": 5, // 椰子殼
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
    return "/world/area/muye/npc/fooder.c";  // 拉麵店老闆
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N驚訝地大喊："HIG"居然帶回來這麼多的甲殼！\n"NOR,
        CYN"$N高興的跳起舞來!!!\n"NOR,
        "$N對著$n說道："HIG"能把店裡佈置的這麼華麗全都靠$n幫忙！\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習點數 1000 點。\n";
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
    player->add_point("learn", 1000);
    tell_object(player, HIY"(你獲得了 1000 點學習點數。)\n"NOR);
}
