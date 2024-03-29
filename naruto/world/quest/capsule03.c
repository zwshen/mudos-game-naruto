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
    return "必要的收集３";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "為了獲得藥山洨所製作的神奇膠囊，你必須滿足他的條件，就是幫他\n";
    msg += "收集他夢寐以求的一些收藏品。藥山洨除了是位製藥師，同時也是位\n";
    msg += "收藏者，雖然他收集的東西都蠻奇怪的...\n";

    return msg;
}

// 任務等級
int getLevel() {
    return 40;
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
    if( player->query("level") > 49 ) return 0;
    if( player->query("level") < 40 ) return 0;
    if( !player->query("capsule_pill", 1) ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/blood_wild/npc/pill.c";  // 山之男藥山洨
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$n向$N尋問有關神奇膠囊的事情...\n"NOR,
        "$N說道："HIG"呵呵，那可是我精心製作的秘藥。\n"NOR,
        "$N說道："HIG"吃下去有如重獲新生，所以我叫他「重生膠囊」\n"NOR,
        "$N說道："HIG"想要嗎？想要就去幫我搜集一些我要的收藏品。\n"NOR
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/sand_hole/npc/doctor.c": 2,     // 沙賊醫生
        "/world/area/sand_hole/npc/bandit.c": 15,    // 沙賊
    ]);
    return kill;
}

// 任務須要取得某些物品，若不需要則 return 0
// 注意：這些物品必需是複合型物件才行
mapping getItem() {
    mapping item = ([
        "/world/area/bone/npc/item/paper.c": 10,           // 輝夜之證
        "/world/area/sneakhole/npc/item/sample.c": 5,      // 蛇毒
        "/world/area/thorn_pine/npc/item/owl_plume.c": 10, // 梟羽
        "/world/area/muye/npc/item/kiss_book.c": 1,        // 親熱天堂
        "/world/area/old_forest/npc/item/fruit4.c": 20,    // 水果王
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
    return "/world/area/blood_wild/npc/pill.c";  // 山之男藥山洨
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"沒錯！就是這些東西！\n"NOR,
        "$N說道："HIG"$n做的不錯，現在讓我來製作藥品。\n"NOR,
        "$N痛苦地說道："HIG"雖然是秘藥，但是我還無法控制藥品的效果。\n"NOR,
        "$N痛苦地說道："HIG"總之先做出來就是了。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = RED"重"HIW"生"HIK"膠囊"NOR"一粒。\n";
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
    object pill;

    switch( random(4) ) {
        case 0: pill = new("/world/capsule/_str.c"); break;
        case 1: pill = new("/world/capsule/_con"); break;
        case 2: pill = new("/world/capsule/_dex.c"); break;
        case 3: pill = new("/world/capsule/_int.c"); break;
    }
    message_vision(CYN"\n$N將材料放進機器中按下開關，四周風雲變色，發出霹靂啪啦的閃電雷光。\n"NOR, npc, player);
    if( pill->move(player) )
        message_vision(CYN"$N擦擦額頭上的汗滴，將"NOR+pill->query("name")+NOR+CYN"取出慎重地交給$n。\n\n"NOR, npc, player);
    else {
        // 因為此藥每個等級的需求物品不同
        // 所以不允許掉在地上給其他人撿
        // 如果身上過重就當成製藥失敗直接不見
        message_vision(HIR"機器忽然轟隆一聲，將四周炸成一片焦黑。\n\n"NOR, npc, player);
        destruct(pill);
    }
}
