#include <ansi.h>

// 說明這是一個陣營檔
int isCamp() { return 1; }

// 陣營名稱
string getName() { return "半獸人"; }

// 友好陣營
string* getFriendly() { return ({}); }

// 敵對陣營
string* getAdversely() { return ({ "snaker" }); }

// (4) 崇拜, (3) 崇敬, (2) 尊敬, (1) 友好, (0) 中立, (-1) 冷淡, (-2) 敵視, (-3) 敵對, (-4) 仇恨

// 玩家在該陣營的聲望低於多少時會被Auto kill，預設的值是-3
int getHate() { return -3; }

// Auto Kill 時，所要喊的話, $N是自已, $n是對方
string getHateMsg() {
    return HIR"$N一見到$n有如深仇大恨般的嘶喊道：「納命來！狗賊！」。\n"NOR;
}

// 玩家在敵對陣營的聲望高於多少時會被Auto kill, 預設的值是 3
int getAdvHate() { return 3; }

// 目對敵對陣營時Auto kill要喊的話, $N時自已, $n是對方
string getAdvHateMsg() {
    return HIR"$N一見到$n有如深仇大恨般的嘶喊道：「蛇人的走狗！納命來！」。\n"NOR;
}
