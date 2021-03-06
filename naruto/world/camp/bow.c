#include <ansi.h>

// 說明這是一個陣營檔
int isCamp() { return 1; }

// 陣營名稱
string getName() { return "豹族"; }

// 友好陣營
string* getFriendly() { return ({}); }

// 敵對陣營
string* getAdversely() { return ({ "owl" }); }

// (4) 崇拜, (3) 崇敬, (2) 尊敬, (1) 友好, (0) 中立, (-1) 冷淡, (-2) 敵視, (-3) 敵對, (-4) 仇恨

// 玩家在該陣營的聲望低於多少時會被Auto kill，預設的值是-3
int getHate() { return -3; }

// Auto Kill 時，所要喊的話, $N是自已, $n是對方
string getHateMsg() {
    switch( random(3) ) {
        case 0: return HIR"$N看到是$n就像發了瘋似的衝上來吼著：豹族的敵人別跑！\n"NOR; break;
        case 1: return HIR"$N指著$n大叫：就是$n！就是$n殺了隔壁老王的孩子！\n"NOR; break;
        case 2: return HIR"$N悲憤地吼叫著：可惡的$n害我們損失了多少同胞！\n"NOR; break;
    }
}

// 玩家在敵對陣營的聲望高於多少時會被Auto kill, 預設的值是 3
int getAdvHate() { return 3; }

// 目對敵對陣營時Auto kill要喊的話, $N時自已, $n是對方
string getAdvHateMsg() {
    return HIR"$N吼道：$n就是幫助蒼之梟搶走我們地盤的人吧！$n沒資格出現在這裡！\n"NOR;
}
