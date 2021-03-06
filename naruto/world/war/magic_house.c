// magic_house.c
//
#define OPEN_WAR 0
#include <ansi.h>
inherit F_DBASE;

// 表示是一個戰爭檔
int isWar() { return 1; }

// 戰爭的持續時間
// 如果設為0, 表示戰爭的持續時間自行設定，不由系統控制
int getDuration() { return 0; }   // 時間由怪物控制吧

private void create() 
{
    seteuid(getuid());
    set("channel_id", "戰爭精靈");
}

private int getPlayerCnt(object area)
{
    int i, size, cnt = 0;
    object *inv;

    inv = all_inventory(area);
    size = sizeof(inv);

    for(i=0; i<size; i++)
        if( userp(inv[i]) ) cnt += 1;

    return cnt;
}

private void moveCorrectCoord(object mob, object room)
{
    int x, y, ok = 0;

    while( ok == 0 ) {
        x = random(41);
        y = random(26);

        if( !room->query_data(x, y, "block") )
            ok = 1;
    }
    area_move(room, mob, x, y);
}

private void createBandit(object player, object room)
{
    object mob;
    int i;
    int cnt = 20;  // cnt = random(60) + 70 一次太多會有問題
    string npc_path = "/world/area/magic_house/npc/";

    // 其它雜魚
    for(i=0; i<cnt; i++) {
        mob = new(npc_path + "monster.c");
        moveCorrectCoord(mob, room);
    }
}

// 開始戰爭所要執行的操作
// 傳回 1 表示戰爭啟動, 0 表示沒啟動
int doStartWar(object player)
{
    object room;

    // 取得某區域
    room = load_object("/world/area/magic_house/house.c");

    // 沒辦法載入區域
    if( !objectp(room) ) return 0;

    // 因為有 call out 所以將敘述放在這裡
    // 有玩家會嫌吵，所以戰爭的訊息都放到 war 裡
    CHANNEL_D->do_channel( this_object(), "war",HIW"大膽的"+player->query("name")+"將魔術馬戲團的野獸籠子打開拉...！！\n\n"NOR+HIG"\t魔術馬戲團內一片狼藉，遊客到處逃命，小丑們忙著補捉野獸\n\n"NOR);

    // 用這個去給 mob 判斷該不該留在區域中，減少 map 的負擔
    room->set("MONSTER_WAR", 1);

    // 載入相關NPC
    createBandit(player, room);
    call_out("createBandit", 5, player, room);
    call_out("createBandit", 10, player, room);
    call_out("createBandit", 15, player, room);

    return 1;
}

// 結束戰爭所要執行的操作
// 傳回 1 表示戰爭結束, 0 表示沒結束
int doEndWar(object player)
{
    object home, room;

    // 取得某區域
    room = load_object("/world/area/magic_house/house.c");

    // 因為要讓開關重新啟用
    home = load_object("/world/area/magic_house/open.c");

    // 沒辦法載入區域
    if( !objectp(room) ) return 0;

    // 結束了要刪除
    home->delete("MONSTER_WAR");
    room->delete("MONSTER_WAR");
    CHANNEL_D->do_channel( this_object(), "war", HIW"野獸們終於被抓回籠子拉，真是可喜可賀..."NOR);
    return 1;
}

void doHeartBeat()
{
}
