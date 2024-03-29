#include <ansi.h>
inherit F_CLEAN_UP;

string duration()
{
    int t, d, h, m, s;
    string time;

    t = uptime();
    s = t % 60;
    t /= 60;
    m = t % 60;
    t /= 60;
    h = t % 24;
    t /= 24;
    d = t;

    if (d)
        time = d + "天";
    else
        time = "";

    if (h)
        time += h + "小時";
    if (m)
        time += m + "分";
    time += s + "秒";

    return time;
}

int main(object me, string arg)
{
    write("\nMUD 名稱：" + MUD_NAME + "\n");
    write("驅動環境：" + __ARCH__ + "\n");
    write("驅動版本：" + __VERSION__ + "\n");
    write("執行效率：" + query_load_average() + "\n");
    write("內存佔用：" + memory_info() / 1024 / 1024 + "M\n");
    write("運行時間：" + duration() + "\n");
    write("註冊用戶：" + sizeof(get_dir(DATA_DIR "user/*.o")) + "人\n");
    write("在線玩家：" + sizeof(users()) + "人\n");
    write("遊戲生物：" + sizeof(livings()) + "位\n");
    write("載入對象：" + sizeof(objects()) + "個\n");

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : mudinfo

查看遊戲基本信息。

HELP );
    return 1;
}
