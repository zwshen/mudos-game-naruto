/* help.c 查看說明文件指令
   create by Acme 2007.03.07
*/
#include <ansi.h>
#include "/doc/help.h"

#define ROOT "/doc/help/"

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

void doHelp(object me);

void doBack(object me)
{
    int size;
    string *path;

    if( !me->query("help") ) {
        doHelp(me);
        return;
    }

    path = explode(me->query("help"), "/");
    
    size = sizeof(path);

    if( sizeof(path) && path[sizeof(path)-1] == "" ) size -= 1;

    if( size <= 1 ) {
        me->delete("help");
    } else {
        int i;
        string new_path = "";
        for(i=0;i<size-1;i++)
            new_path += path[i] + "/";
        me->set("help", new_path);
    }
}

void doRoot(object me)
{
    me->delete("help");
    doHelp(me);
}

void folderCheck(string input, object me, mixed *files)
{
    int index;

    if( !input ) {
        tell_object(me, "請選擇？");
        input_to("folderCheck", me, files);
        return;
    }
    
    if( sscanf(input, "%d", index) == 1 ) {
        if( !sizeof(files) ) {
            tell_object(me, "請選擇？");
            input_to("folderCheck", me, files);
            return;
        } else {
            index--;
            if( index < 0 || index >= sizeof(files) ) {
                tell_object(me, "請選擇？");
                input_to("folderCheck", me, files);
                return;
            }
        }
    } else {
       if( input == "q" ) return;
       else if( input == "b" ) {
           doBack(me);
           doHelp(me);
           return;
       } else if( input == "r") {
           doRoot(me);
           return;
       } else {
           tell_object(me, "請選擇？");
           input_to("folderCheck", me, files);
           return;
       }
    }

    // 是一個目錄
    if( files[index][1] == -2 )
        me->set("help", (me->query("help") ? me->query("help"):"") + files[index][0] + "/" );
    else me->set("help", (me->query("help") ? me->query("help"):"") + files[index][0]);

    doHelp(me);
}

mapping getTopic(string dir)
{
    int i = 0;
    string read;
    mapping topic = ([]);
    dir = ROOT + dir + "topic";
    
    while( (read=read_file(dir, i, 1)) ) {
       string eng, chi;
       
       if( sscanf(read, "%s,%s\n", eng, chi) == 2 ) 
           topic[eng] = chi;
       else if( sscanf(read, "%s,%s", eng, chi) == 2 ) 
           topic[eng] = chi;
       i++;
    }

    return topic;
}

void printFolder(object me, string dir)
{
    int i;
    string file;
    mapping topic;
    mixed *files;

    files = get_dir(ROOT+dir, -1);

    if( wizardp(me) ) write(MUD_NAME+"說明文件，目前位置 " + HIC+ROOT+HIY+dir+NOR +"\n");
    else write(MUD_NAME+"說明文件，目前位置 " + HIY+"/"+dir+NOR + "\n");
    write(HIW"�������������������������������������������������������������������鱭n"NOR);

    topic = getTopic(dir);

    for(i=0;i<sizeof(files);i++) {
        file = files[i][0];
        
        // 如果列出的是目錄，加上一個 '/'
        if( files[i][1] == -2 ) {
            file += "/";
            write(sprintf(" %2d. "HIC"%-45s "HIK"(%s)\n"NOR, i+1, (undefinedp(topic[file]) ? file : topic[file]), file));
        } else {
            if( file == "topic" )
                write(sprintf(" %2d. "HIB"%-45s "HIK"(%s)\n"NOR, i+1, (undefinedp(topic[file]) ? file : topic[file]), file));
            else write(sprintf(" %2d. "WHT"%-45s "HIK"(%s)\n"NOR, i+1, (undefinedp(topic[file]) ? file : topic[file]), file));
        }
    }
    write(HIW"��������������������������  回根目錄("HIY"r"HIW"), 前一個目錄("HIY"b"HIW"), 離開("HIY"q"HIW") ���鱭n"NOR);
    write("請選擇？");

    input_to("folderCheck", me, files);
}

void fileCheck(string input, object me)
{
    int index;

    if( !input ) {
        tell_object(me, "請選擇？");
        input_to("fileCheck", me);
        return;
    }
    
    if( input == "q" ) return;
    else if( input == "b" ) {
        doBack(me);
        doHelp(me);
        return;
    } else if( input == "r") {
        doRoot(me);
        return;
    } else {
        tell_object(me, "請選擇？");
        input_to("fileCheck", me);
        return;
    }
}

void printFile(object me, string dir)
{
    if( file_size(ROOT+dir) == -1 ) { // 檔案不存在
        me->delete("help");
        doHelp(me);
        return;
    }

    if( wizardp(me) ) write(MUD_NAME+"說明文件，目前位置 " + HIC+ROOT+HIY+dir+NOR +"\n");
    else write(MUD_NAME+"說明文件，目前位置 " + HIY+"/"+dir+NOR + "\n");
    write(HIW"�������������������������������������������������������������������鱭n"NOR);

    if( file_size(ROOT+dir) > 1000 ) {
        me->start_more( read_file(ROOT+dir) );
        doBack(me);
    } else {
        write(read_file(ROOT+dir));
        write(HIW"\n��������������������������  回根目錄("HIY"r"HIW"), 前一個目錄("HIY"b"HIW"), 離開("HIY"q"HIW") ���鱭n"NOR);
        write("請選擇？");
        input_to("fileCheck", me);
    }
}

void doHelp(object me)
{
    int size;
    string dir;
    
    if( !(dir = me->query("help")) ) dir = "";

    size = file_size( ROOT+dir );
    
    if( size == -1 ) {        // 檔案不存在
        me->delete("help");
        printFolder(me, "");  // 顯示根目錄
    } else if( size == -2 ) { // 是一個目錄
        printFolder(me, dir); // 顯示目前的目錄
    } else {                  // 檔案存在
        printFile(me, dir);   // 顯示檔案內容
    }
}

int main(object me, string arg)
{
    string help, file, *search;

    if( !arg ) {
        doHelp(me);
        return 1;
    }

    help = arg[1..strlen(arg)-1];

    if( file_size(ROOT+help) == -1 ) {    //檔案不存在
        if( wizardp(me) ) {
            if( file_size(arg) == -1 ) { //檔案不存在
                notify_fail("沒有這個說明文件。\n");
            } else {
                if( sscanf(arg, ROOT+"%s", help) == 1 ) {
                    me->set("help", help);
                    doHelp(me);
                    return 1;
                } notify_fail("沒有這個說明文件。\n");
            }
        } else notify_fail("沒有這個說明文件。\n");
    } else {
        me->set("help", help);
        doHelp(me);
        return 1;
    }

    arg = replace_string(arg, " ", "_");
    if( stringp(file = me->find_command(arg)) ) {
        notify_fail("有這個指令存在﹐但是並沒有詳細的說明文件。\n");
        return file->help(me);
    }

    if( !wizardp(me) ) return 1;

    sscanf(arg, "%s()", arg);

    search = WIZARD_SEARCH_PATHS;

    foreach(string path in search) {
        if( file_size(path + arg) < 0 ) continue;
        if( wizardp(me) )
            write("說明文件：" + path + arg +
                  "\n---------------------------------------------------------------------\n"
            );
        me->start_more( read_file(path + arg) ); 
        return 1;
    }

    return notify_fail("沒有針對這項主題的說明文件。\n");
}

int help(object me)
{
    write(@HELP
指令格式：
    help                 進入 help 檢索功能
    help <指令>          例如﹕help score
    help <文件位置>      例如﹕help /setup/world  (也可以是一個目錄)

這個指令提供你針對某一主題的詳細說明文件﹐若是不指定主題﹐則提供你有關主題
的文件﹐所有的主題與函數名稱皆為英文。
HELP
    );
}
