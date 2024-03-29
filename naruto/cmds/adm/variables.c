inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
    object ob, env;
    string *vars, id;

    if (!wizardp(me))
        return 0;

    if (!arg || arg == "me" || arg == "")
        ob = me;
    else if (arg == "here")
        ob = environment(me);
    else if (sscanf(arg, "%s in %s", arg, id) == 2)
    {
        env = present(id, environment(me));
        if (!env)
            env = present(id, me);
        if (!env)
            return notify_fail("當前環境中沒有找到對象 " + id + "。\n");
        if (!ob = present(arg, env))
            return notify_fail("環境 " + id + " 中沒有找到對象 " + arg + "。\n");
    }
    else
    {
        // arg = lower_case(arg);

        ob = present(arg, environment(me));
        if (!ob)
            ob = find_player(arg);
        if (!ob)
            ob = find_living(arg);
        if (!ob)
            ob = present(arg, me);
        if (!ob)
            ob = load_object(arg);
        if (!ob)
            return notify_fail("無法找到對象 " + arg + "。\n");
    }
    if (sizeof(vars = variables(ob, 1)))
        foreach (string *var in vars)
            if (strsrch(var[1], "private") == -1)
                printf("%s = %O\n", var[0], fetch_variable(var[0], ob));
            else
                printf("%s 是 %s 類型變量。\n", var[0], var[1]);

    return 1;
}
