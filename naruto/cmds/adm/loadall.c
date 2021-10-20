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
        return notify_fail(dir + "�ؿ����s�b�P�P�P\n");
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
            //�L�kŪ�����ؿ��A���L
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
���J���w�ؿ��Τl�ؿ��U���Ҧ�.c���A��K�d��i��s�b���sĶ���~�C

���O�榡�G loadall [dir]
    ��p�G loadall /cmds/
    �p�G�����w dir �h�q�{�� /

HELP);
    return 1;
}
