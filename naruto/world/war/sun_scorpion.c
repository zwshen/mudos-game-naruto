// 蠍子
//
#define OPEN_WAR 0
#include <ansi.h>
inherit F_DBASE;

// 表示是一個戰爭檔
int isWar() { return 1; }

// 戰爭的持續時間
// 如果設為0, 表示戰爭的持續時間自行設定，不由系統控制
int getDuration() { return 600; }   // 持續 10 分鐘 (600秒)

object *loadMobs = ({});

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
        x = 22;
        y = 29;

        if( !room->query_data(x, y, "block") )
            ok = 1;
    }
    area_move(room, mob, x, y);
}

private void createBandit(object player, object room)
{
    object mob;
    string npc_path = "/world/area/sand_hole/npc/";

    mob = new(npc_path + "sun_scorpion.c");
    moveCorrectCoord(mob, room);

    // 數量少就交給 map 去判斷吧..希望沒問題 @o@
    loadMobs += ({ mob });

    CHANNEL_D->do_channel( this_object(), "war", HIR"地面陣陣的搖動，一聲巨響赫然傳遍四周\n\n"NOR+HIW"只見那碎骨寨附近的天空忽然閃耀著如太陽般的光芒，與天空的陽光相互呼應\n\n"NOR);
}

// 開始戰爭所要執行的操作
// 傳回 1 表示戰爭啟動, 0 表示沒啟動
int doStartWar(object player)
{
    object room;

    // 取得某區域
    room = load_object("/world/area/sand_hole/hole_3b.c");

    // 沒辦法載入區域
    if( !objectp(room) ) return 0;

    // 載入相關NPC
    createBandit(player, room);

    return 1;
}

// 結束戰爭所要執行的操作
// 傳回 1 表示戰爭結束, 0 表示沒結束
int doEndWar(object player)
{
    // 刪掉載入的mob
    int i, size;
    object home;

    // 因為要讓開關重新啟用
    home = load_object("/world/area/sand_hole/hole_3b.c");

    size = sizeof(loadMobs);
    for(i=0; i<size; i++) {
        if( objectp( loadMobs[i] ) ) {
            message_vision("時間的流逝金銀雙杯又再次乾涸，$N也回到沉眠之中。\n"NOR, loadMobs[i]);

            // 表示 mob 有被刪除時才有敘述，對單隻的 mob 可以放在這裡
            // 避免和 boss 級 mob 死掉大喊重複 end
            // 結束的敘述是由此程式提供
             CHANNEL_D->do_channel( this_object(), "war", HIC"天搖地動漸漸停了，彷彿什麼事情也沒發生"NOR);
            destruct(loadMobs[i]);
        }
    }
    loadMobs = ({});
    return 1;
}

void doHeartBeat()
{
}
