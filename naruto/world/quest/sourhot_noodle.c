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
    return "老張酸辣麵";
}

// 任務描述
string getDetail() {
    string msg;

    msg  = "雖然老張因為女兒被蛇人綁走而心情鬱悶，但是也不希望自己的手藝\n";
    msg += "就此失傳，因此在你千萬拜託之下，老張決定將他除了牛肉麵的另一\n";
    msg += "拿手絕活「酸辣麵」傳授給你，希望在老張頹廢的教導下你能夠如願\n";
    msg += "學會這項絕技。\n";

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
    return "/world/area/echo/npc/zhang.c";  // 老張
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
     CYN"$n想向$N拜師，但是卻被$N一口回絕了。\n"NOR,
        "$N說道："HIG"我女兒已經被抓走好幾十天了，哪還有心情收徒授業！\n"NOR,
        "$n說道："HIG"難道您希望您的手藝就此失傳嗎！\n"NOR,
        "$n說道："HIG"就算您因此不在做麵，讓我幫助您繼續服務大眾吧！\n"NOR,
     CYN"$N聽聞後愣了一下，緩緩地嘆了口氣。\n"NOR,
        "$N說道："HIG"好吧！我也不想讓我的手藝失傳！\n"NOR,
        "$N說道："HIG"$n去把酸辣麵的材料搜集回來，我就教你製作酸辣麵！\n"NOR,
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
        "/world/area/rural_area/npc/item/chile.c": 5,    // 辣椒醬
        "/world/area/rural_area/npc/item/soy.c": 1,      // 醬油
        "/world/area/rural_area/item/powder02.c": 1,     // 辣椒粉
        "/world/area/rural_area/item/pill_obj04.c": 5,   // 小辣椒
        "/world/area/rural_area/item/pill_obj01.c": 5,   // 菠菜
        "/world/area/rural_area/item/pill_obj02.c": 10,  // 紅蘿蔔
        "/world/area/rural_area/npc/item/sugar.c": 5,    // 糖
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
    return "/world/area/echo/npc/zhang.c";  // 老張
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
     CYN"$N看著$n準備的材料，滿意的點點頭。\n"NOR,
        "$N說道："HIG"準備好了就開始吧，把辣椒全切了爆香。\n"NOR,
        "$N說道："HIG"然後放入切細的菠菜紅蘿蔔，加入酸菜湯頭。\n"NOR,
        "$N說道："HIG"等湯滾了再加入辣椒粉，適量辣椒醬和糖調味。\n"NOR,
        "$N說道："HIG"醬油配色，然後下麵，完工。\n"NOR,
     CYN"$n正聽的仔細，忽然一愣才想到前一句話，完工？\n"NOR,
    });

    return msg;
}

string getReward()
{
    string msg = "學習酸辣麵。\n";
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

    item = new("/world/area/echo/npc/item/noodle2.c");
    if( item->move(player) )
        tell_object(player, HIY"(你獲得了一碗酸辣麵。)\n"NOR);
    else {
        // 將給的物品移到與玩家同一格的area區域中
        // 如果是在 area 中，把item移到player所處的座標位置
        if( environment(player)->is_area() ) move_side(item, player);
        // 如果是在 room 中，把item移到player所處的房間中
        else item->move(environment(player));
        tell_object(player, HIY"(你獲得了一碗酸辣麵，但是掉在地上了。)\n"NOR);
    }
    message_vision("\n$N說道："HIG"$n學會酸辣麵了吧，快去服務大眾別來煩我了。\n"NOR, npc, player);
    message_vision("$n困惑地說道："HIG"師傅您剛才說太快了...我沒記清楚...\n"NOR, npc, player);
    message_vision(CYN"$N滿臉悲痛的低聲喊著：誰能救救我的女兒阿！\n"NOR, npc, player);
    message_vision("$n困惑地說道："HIG"師傅？...\n"NOR, npc, player);
    message_vision(CYN"$N滿臉悲痛的低聲喊著：誰能救救我的女兒阿！\n"NOR, npc, player);
    message_vision("$n說道："HIG"......\n"NOR, npc, player);
    message_vision(CYN"$N滿臉悲痛的低聲喊著：誰能救救我的女兒阿！\n"NOR, npc, player);
    tell_object(player, HIY"(你心裡一想...算了就當做花時間買碗麵吧。)\n"NOR);
}
