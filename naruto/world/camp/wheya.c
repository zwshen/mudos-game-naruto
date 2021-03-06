#include <ansi.h>

// 說明這是一個陣營檔
int isCamp() { return 1; }

// 陣營名稱
string getName() { return "竹取一族"; }

// 友好陣營
string* getFriendly() { return ({ "music" }); }

// 敵對陣營
string* getAdversely() { return ({ "snaker", "muye" }); }

// (4) 崇拜, (3) 崇敬, (2) 尊敬, (1) 友好, (0) 中立, (-1) 冷淡, (-2) 敵視, (-3) 敵對, (-4) 仇恨

// 玩家在該陣營的聲望低於多少時會被Auto kill，預設的值是-3
int getHate() { return -2; }

// Auto Kill 時，所要喊的話, $N是自已, $n是對方
string getHateMsg() {
    switch( random(3) ) {
        case 0: return HIR"$N說道：得罪了竹取一族，$n就只有死路一條！\n"NOR; break;
        case 1: return HIR"$N擺出備戰的姿態，一言不發就攻擊$n！\n"NOR; break;
        case 2: return HIR"$N指著$n說道：就是$n沒事來這裡搗亂，竹取一族豈能容$n撒野！\n"NOR; break;
    }
}

// 玩家在敵對陣營的聲望高於多少時會被Auto kill, 預設的值是 3
int getAdvHate() { return 3; }

// 目對敵對陣營時Auto kill要喊的話, $N時自已, $n是對方
string getAdvHateMsg() {
    return HIR"$N對著$n抱拳說道：大蛇丸大人有令不能放過木葉忍者，就請$n賜招吧！\n"NOR;
}
