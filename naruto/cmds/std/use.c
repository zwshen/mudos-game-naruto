// use.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string str, item;
    object ob;

    if( me->is_busy() ) return notify_fail("你現在沒有空。\n");
    if( !arg || arg=="" ) return notify_fail("你要使用什麼東西？\n");

    if( sscanf(arg, "%s to %s", item, str)  == 2 ) {
        ob = present(item, me);
        if( !ob ) ob = present(item, environment(me));
        if( !ob ) return notify_fail("這裡沒有這樣東西...\n");
    } else if( sscanf(arg, "%s on %s", item, str) == 2 ) {
        ob = present(item, me);
        if( !ob ) ob = present(item, environment(me));
        if( !ob ) return notify_fail("這裡沒有這樣東西...\n");
    } else {
        ob = present(arg, me);
        if( !ob ) ob = present(arg, environment(me));
        if( !ob ) return notify_fail("這裡沒有這樣東西...\n");
        str = "";
    }

    if( !function_exists("do_use", ob) )
       return notify_fail("這樣東西似乎不能使用什麼...\n");

    ob->do_use(me, str);

    return 1;
}

int help()
{
    write(@TEXT
指令格式：use <物品>

這個指令可以讓你使用特殊物品。
TEXT);
    return 1;
}
