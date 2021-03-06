// 蠍子
//
#define OPEN_WAR 0
#include <ansi.h>
inherit F_DBASE;

// 表示是一個戰爭檔
int isWar() { return 1; }

// 戰爭的持續時間
// 如果設為0, 表示戰爭的持續時間自行設定，不由系統控制
int getDuration() { return 300; }   // 持續 5 分鐘 (300秒)

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
    CHANNEL_D->do_channel( this_object(), "war", HIR"\n\n\t某人不怕死的闖入火山的深處，結果卻導致火山加速活化..."NOR"\n\n\t"HIK"只見偉大的航道上空中噴出陣陣濃煙..."NOR"\n\n\t"HIY"看來再過"BLINK"五分鐘"NOR+HIY"左右這座火山島嶼就撐不住了！\n\n\n"NOR);
}

// 開始戰爭所要執行的操作
// 傳回 1 表示戰爭啟動, 0 表示沒啟動
int doStartWar(object player)
{
    object room;

    // 取得某區域
    room = load_object("/world/area/lv60_area/fire.c");

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
    object room;
    object *inv;

    // 要讓區域中的玩家全部燒死
    room = load_object("/world/area/lv60_area/fire.c");

    inv = all_inventory(room);
    size = sizeof(inv);

    CHANNEL_D->do_channel( this_object(), "war",HIR"\n\n\t火山爆發啦！還在火山中逗留的冒險者們都受到無情的炎龍所吞噬...\n\n\n"NOR);

    for(i=0; i<size; i++) if( userp(inv[i]) ) inv[i]->die();
    loadMobs = ({});
    return 1;
}

void doHeartBeat()
{
}
