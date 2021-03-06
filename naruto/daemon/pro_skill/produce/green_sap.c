// 綠色樹液製造 green_sap.c
#include <ansi.h>

// 屬於生產技能下的產品
string getProSkill() { return "produce"; }

// 習得此產品必要的技能等級
int getLearnLevel() { return 0; }

// 物品名稱
string getName() { return "綠色樹液"; }

// 簡述
string getBrief() {
    return "綠色的樹木液體，能做什麼用呢？";
}

// 詳述
string getDetail() {
    return "使用綠色蔬菜提煉出來的液體，因為是原汁，無法當蔬菜汁食用。\n";
}

// 製造此產品所需的材料
mapping getStuff() {
    mapping stuff = ([
        "/world/area/rural_area/item/pill_obj01.c": 1,  // 菠菜
        "/world/area/rural_area/item/pill_obj03.c": 1,  // 芹菜
    ]);
    return stuff;
}

// 製造的產品檔
string getProduct() {
    return "/world/area/thorn_pine/npc/item/water01.c";  // 綠色樹液
}

// 製造產品時的訊息
string makeMsg()
{
    return HIG"$N拿起搗缽將材料全部丟進缽中，開始榨取綠色樹液。\n"NOR;
}

// 產品是否綁定(也就是製造的人才能用), (1:是, 0:否)
// 註：綁定的產品最好是不能合併的物品，否則綁定會混亂
//     綁定的產品上會設定 set("binding", 角色id)
//     所以要判斷該產品是否能被使用就是檢查 binding 是否符合玩家的id就行了
int isBinding() { return 0; }
