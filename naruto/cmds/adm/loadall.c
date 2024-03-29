#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);
int loadall(string dir);

int main(object me, string dir)
{
    if (!wizardp(me))
        return 0;

    if (!dir)
        dir = "/";
    if (dir[ < 1] != '/')
        dir += "/";
    if (file_size(dir) != -2)
        return notify_fail(dir + "目錄不存在···\n");
    log_file("loadall", "\n#check dir : " + dir);
    write("check dir " + dir + "\n");
    if (loadall(dir))
        return 1;
}

int loadall(string dir)
{
    string file, err, *dirs;

    if (!arrayp(get_dir(dir)))
        return 1;

    dirs = get_dir(dir);
    if (dir == "/")
        dirs = dirs - ({".git", ".vscode", "bin",
                        "data", "doc", "include",
                        "log", "u", "www"});

    foreach (file in dirs)
    {
        if (member_array(file, ({"simul_efun", "master"})) > -1)
            continue;

        reset_eval_cost();
        switch (file_size(dir + file))
        {
        case -1:
            //無法讀取的目錄，跳過
            break;
        case -2:
            if (file != "." && file != "..")
                call_out("loadall", 1, dir + file + "/");
            break;
        default:
            if ((dir + file)[ < 2.. < 1] == ".c")
            {
                if (err = catch (load_object(dir + file)))
                    log_file("loadall", "\n\tcheck : " + dir + file + "\n" + err);
            }
        }
    }
    write("check dir " + dir + " is ok.\n");
    return 1;
}

int help(object me)
{
    if (!wizardp(me))
        return 0;

    write(@HELP
載入指定目錄及子目錄下的所有.c文件，方便查找可能存在的編譯錯誤。

指令格式： loadall [dir]
    比如： loadall /cmds/
    如果不指定 dir 則默認為 /

HELP);
    return 1;
}
