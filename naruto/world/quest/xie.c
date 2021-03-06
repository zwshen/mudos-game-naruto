#include <ansi.h>

void create() { seteuid(getuid()); }

int isQuest() { return 1; }
int isNewly() { return 0; }
string getName() { return "鯨魚島忙碌的廚師"; }

string getDetail() {
    string msg;
        
    msg  = "近年來真是越來越忙了，訂單接都接不完...\n";
    msg += "蟹肉用料越用越兇，不知道有沒有人能幫忙搜集呢...\n";
    msg += "幫忙屠千蟹搜集十個蟹肉。\n";
    return msg;
}

int getLevel() { return 5; }
int preCondition(object player) { return 1; }
int postCondition(object player, object npc) { return 1; }

string getAssigner() { return "/world/area/whale_island/npc/tu-qian-xie.c"; }
string getRewarder() { return "/world/area/whale_island/npc/tu-qian-xie.c"; }

string *getAssignMessage() {
    string *msg = ({
        "$N對著$n說道："HIG"近年來真是越來越忙了，訂單接都接不完...\n"NOR,
        "$N對著$n說道："HIG"蟹肉用料越用越兇，不知道有沒有人能幫忙搜集呢...\n"NOR,
    });        
    return msg;
}

mapping getKill() { return ([]); }

mapping getItem() {
    mapping item = ([
        "/world/area/whale_island/npc/food/crab_meat.c": 10,
    ]);
    return item;
}


// 完成任務時的訊息
string *getRewardMessage() {
    // $N為NPC, $n為player
    string *msg = ({
        "$N對著$n說道："HIG"啊哈∼∼非常謝謝你的幫忙了，這是我的一點報酬，謝謝了。\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    return "一千兩銀子。\n二百點學習點數。\n";
}

void reward(object player, object npc) {
    player->add_point("learn", 200);
    tell_object(player, HIY"(你獲得了 200 點學習點數。)\n"NOR);
    player->add("bank", 1000);
    tell_object(player, HIY"(你獲得了 1000 兩銀子。)\n"NOR);
}
