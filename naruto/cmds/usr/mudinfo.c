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
        time = d + "��";
    else
        time = "";

    if (h)
        time += h + "�p��";
    if (m)
        time += m + "��";
    time += s + "��";

    return time;
}

int main(object me, string arg)
{
    write("\nMUD �W�١G" + MUD_NAME + "\n");
    write("�X�����ҡG" + __ARCH__ + "\n");
    write("�X�ʪ����G" + __VERSION__ + "\n");
    write("����Ĳv�G" + query_load_average() + "\n");
    write("���s���ΡG" + memory_info() / 1024 / 1024 + "M\n");
    write("�B��ɶ��G" + duration() + "\n");
    write("���U�Τ�G" + sizeof(get_dir(DATA_DIR "user/*.o")) + "�H\n");
    write("�b�u���a�G" + sizeof(users()) + "�H\n");
    write("�C���ͪ��G" + sizeof(livings()) + "��\n");
    write("���J��H�G" + sizeof(objects()) + "��\n");

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : mudinfo

�d�ݹC���򥻫H���C

HELP );
    return 1;
}
