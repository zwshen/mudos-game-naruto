#include <ansi.h>

// 說明這是一個陣營檔
int isCamp() { return 1; }

// 陣營名稱
string getName() { return "音隱村"; }

// 友好陣營
string* getFriendly() { return ({ "wheya" }); }

// 敵對陣營
string* getAdversely() { return ({ "muye" }); }

// (4) 崇拜, (3) 崇敬, (2) 尊敬, (1) 友好, (0) 中立, (-1) 冷淡, (-2) 敵視, (-3) 敵對, (-4) 仇恨

// 玩家在該陣營的聲望低於多少時會被Auto kill，預設的值是-3
int getHate() { return -1; }

// Auto Kill 時，所要喊的話, $N是自已, $n是對方
string getHateMsg() {
    switch( random(3) ) {
        case 0: return HIR"$N指著$n喊道：這傢伙就是大蛇丸大人新的宿體！把他抓起來！\n"NOR; break;
        case 1: return HIR"$N說道：音隱村豈是$n說來就來說走就走的地方！\n"NOR; break;
        case 2: return HIR"$N說道：$n倒大楣啦！大蛇丸大人交代我們不能讓$n活著離開！\n"NOR; break;
    }
}

// 玩家在敵對陣營的聲望高於多少時會被Auto kill, 預設的值是 3
int getAdvHate() { return 2; }

// 目對敵對陣營時Auto kill要喊的話, $N時自已, $n是對方
string getAdvHateMsg() {
    return HIR"$N指著$n喊道：$n是木葉村裡頗有名氣的人物阿！把他抓回去領賞！\n"NOR;
}
