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
    return "黑暗的正義";
}

// 任務描述
string getDetail() {
    string msg;

    if( this_player()->query("title") == "世界政府海軍" ) {
        msg  = "斯潘達姆長官所告知的任務，不過再怎麼說這也有點過份，為了向羅\n";
        msg += "布路奇學習武術居然要去殺害海軍的雜役，同樣身為海軍人員....所\n";
        msg += "謂黑暗的正義就是如此嗎，為了學習「"HIW"指槍•斑"NOR"」而損失幾名弱者也\n";
        msg += "無所謂....成功達到目標後直接去找羅布•路奇就可以了，斯潘達姆\n";
        msg += "長官就這樣鬼吼鬼叫的告訴你。「希望你也成為海軍的強者阿！」\n";
    } else if( this_player()->query("title") == "猿山連合軍" ) {
        msg  = "ＣＰ９長官斯潘達姆所告知的任務，為了向羅布路奇學習武術而去殺\n";
        msg += "海軍雜役原來海軍內部是這麼的淤腐，不過這位長官似乎有點笨笨的\n";
        msg += "，居然把這事情告訴了一位海賊還不自覺....為了學習「"HIW"指槍•斑"NOR"」\n";
        msg += "....隨便吧！成功達到目標後直接去找羅布•路奇就可以了，斯潘達\n";
        msg += "姆就這樣鬼吼鬼叫的告訴你。「希望你也成為海軍的強者阿！」\n";
    } else {
        msg  = "如果你看到這行應該是任務出錯了...快找巫師來修理吧。\n";
    }
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
    if( player->query("guild") != "piece" ) return 0;
    if( player->query_skill("gun ban", 1) ) return 0;
    if( player->query_class() == "work_sea" ) return 0;
    if( player->query_class() == "little_sea" ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// 接受任務的NPC  (以檔名來識別)
string getAssigner() {
    return "/world/area/sifa_isle/npc/si.c";   // 斯潘達姆
}

// 接受任務時的訊息
string *getAssignMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N說道："HIG"喔喔喔！$n就是先前那位想跟羅布路奇學習武術的人吧！\n"NOR,
        "$N說道："HIG"只要$n能下手殺死海軍雜役，想加入ＣＰ９也不是問題阿！\n"NOR,
        "$N說道："HIG"能夠獲得一個強者就算損失幾百個弱者也無所謂！\n"NOR,
        "$N說道："HIG"重點是我一定要安全阿！\n"NOR,
    });
    return msg;
}

// 任務須要殺死某些怪物，若不需要則 return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/ship/npc/soldier2.c": 20,     // 海軍雜役
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
    return "/world/area/sifa_isle/npc/lu.c";   // 羅布路奇
}

// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        CYN"$N很奇怪的眼神瞄$n.\n"NOR,
        "$N說道："HIG"算了，既然是長官的命令職業又有什麼差別。\n"NOR,
        "$N說道："HIG"$n就好好學著吧。\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "學習技能「"HIW"指槍•斑"NOR"」\n";
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
    player->set_skill("gun ban", 2);
    tell_object(player, HIY"(經過羅布路奇的指導後，你學到斑的精要了)\n"NOR);
}
