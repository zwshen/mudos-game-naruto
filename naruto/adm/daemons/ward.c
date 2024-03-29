/* ward.c 戰爭精靈
   created by Acme 2007.08.02
*/

// #pragma save_binary

#include <ansi.h>

inherit F_SAVE;

string *start;
mapping controller;

void create()
{
    seteuid(getuid());

    if( !restore() && mapp(controller) ) {
        controller = ([]);
    }

    start = ({});

    // 打開心跳
    set_heart_beat(1);
}

string query_save_file()
{
    return DATA_DIR + "ward";
}

private void doSetWar(string war_file)
{
    if( !undefinedp(controller[war_file]) )
        return;

    controller[war_file] = ([]);
    controller[war_file]["start"] = 0;
    controller[war_file]["cnt"] = random(20);
}

void doScanWar(string dir)
{
    string file;
    mixed *files, *dirent;

    if( !stringp(dir) ) dir = "/world/war/";

    files = get_dir(dir, -1);

    if( !sizeof(files) ) {
        if( file_size(dir) == -2 ) write("QUESTD: 戰爭目錄是空的。 (" + dir + ")\n");
        else write("QUESTD: 沒有這個戰爭目錄。 (" + dir + ")\n");
        return;
    }

    // 清空，整個重掃
    controller = ([]);

    write("掃瞄戰爭中 " + dir + " ...\n\n");

    foreach( dirent in files ) {
        file = dir + dirent[0];
        write( sprintf("%-60s", file) );

        if( !file->isWar() ) {
            write( " -> 非戰爭檔.\n");
            continue;
        }

        doSetWar(file);
        write(" -> OK.\n");
    }

    write("\n掃瞄完成。\n\n");
    
    save();
}

// 開始戰爭
int doStartWar(object player, string war_file)
{
    if( undefinedp(controller[war_file]) ) return 0;
    if( member_array(war_file, start) != -1 ) return 0;
    if( controller[war_file]["start"] != 0 ) return 0;

    if( war_file->doStartWar(player) == 0 ) return 0;

    start += ({ war_file });
    controller[war_file]["start"] = time();
    controller[war_file]["duration"] = war_file->getDuration();

    return 1;
}

// 結束戰爭
int doEndWar(object player, string war_file)
{
    if( undefinedp(controller[war_file]) ) return 0;
    if( controller[war_file]["start"] == 0 ) return 0;
    if( war_file->doEndWar(player) == 0 ) return 0;

    start -= ({ war_file });
    controller[war_file]["start"] = 0;

    return 1;
}

// 每次心跳就檢查目前所有開啟的戰爭中，是否已經有戰爭時間到
protected void heart_beat()
{
    int i, size;
    string war_file;

    size = sizeof(start);

    for(i=0; i<size; i++) {
        war_file = start[i];

        if( undefinedp(controller[war_file]) ) continue;
        if( controller[war_file]["start"] == 0 ) continue;

        // 檢查是否時間到
        if( controller[war_file]["duration"] != 0 ) {
            int nowTime = time();
            int startTime = controller[war_file]["start"];
            int duration = controller[war_file]["duration"];

            if( nowTime - startTime >= duration ) {
                doEndWar(this_object(), war_file);
            }
        }

        // 讓每個戰爭的心跳分開不同時機處理
        if( controller[war_file]["cnt"] > 0 ) {
            controller[war_file]["cnt"]--;
            continue;
        }

        controller[war_file]["cnt"] = random(20);

        // 執行戰爭的心跳
        war_file->doHeartBeat();
    }
}

mapping getController()
{
    return controller;

}

string* getStart()
{
    return start;
}
