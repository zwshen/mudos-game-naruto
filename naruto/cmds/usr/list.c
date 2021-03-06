/* sell.c by -Acme-
*/

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object who;
	string msg;

	if( !environment(me) ) return notify_fail("你現在人在哪裡都不知道了。\n");

    if( arg ) {
		if( objectp(who=present(arg, environment(me))) ) {
			if( !stringp(msg = who->do_list()) )
				return notify_fail("這個人無法 list ...\n");
		} else if( !stringp(msg = environment(me)->do_list(arg)) )
				return notify_fail("這個地方無法 list , 若你是想對人物做 list 請加上ID ...\n");
    } else {
    	if( !stringp(msg = environment(me)->do_list()) )
    		return notify_fail("這個地方無法 list , 若你是想對人物做 list 請加上ID ...\n");
    }

	me->start_more(msg);
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : list [某人/編號]

這指令可以列出某人所正在販賣的物品列表，或是某人可以訓練的技
能列表，若是在當舖裡只需 list 即可列出當舖販賣的物品列表，或
是加上編號可以檢視物品的能力。

相關指令： train, sell, buy
HELP);
    return 1;
}
