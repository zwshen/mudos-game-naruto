#include <ansi.h>

// 說明這是一個陣營檔
int isCamp() { return 1; }

// 陣營名稱
string getName() { return "雨隱村"; }

// 友好陣營
string* getFriendly() { return ({}); }

// 敵對陣營
string* getAdversely() { return ({ "muye" }); }

// (4) 崇拜, (3) 崇敬, (2) 尊敬, (1) 友好, (0) 中立, (-1) 冷淡, (-2) 敵視, (-3) 敵對, (-4) 仇恨

// 玩家在該陣營的聲望低於多少時會被Auto kill，預設的值是-3
int getHate() { return -2; }

// Auto Kill 時，所要喊的話, $N是自已, $n是對方
string getHateMsg() {
    switch( random(3) ) {
        case 0: return HIR"$N忽然大叫起來：讓$n知道與我們雨隱村為敵的下場！\n"NOR; break;
        case 1: return HIR"$N吼道：少看不起雨忍了！讓$n知道我們的厲害！\n"NOR; break;
        case 2: return HIR"$N咆哮著：哪有這麼容易被$n打敗！\n"NOR; break;
    }
}

// 玩家在敵對陣營的聲望高於多少時會被Auto kill, 預設的值是 3
int getAdvHate() { return 1; }

// 目對敵對陣營時Auto kill要喊的話, $N時自已, $n是對方
string getAdvHateMsg() {
    return HIR"$N憤怒的吼叫著：我要讓$n知道！想靠木葉這個大村是沒好下場的！\n"NOR;
}
