/* eat.c */

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int stuff;
    object ob;

    if( me->is_busy() ) return notify_fail("你現在正在忙，沒有空...\n");

    if( !arg || arg=="" ) return notify_fail("你要吃什麼﹖\n");

    ob = present(arg, me);
    if( !ob ) ob = present(arg, environment(me));
    if( !ob ) return notify_fail("這裡沒有這樣東西...\n");

    stuff = ob->query("food_stuff");
    if( !stuff ) {
        return notify_fail("這樣東西不能吃...\n");
    }

    // 附有長效狀態效果的食物，不能在戰鬥中使用
    if( ob->query("condition") && me->is_fighting() ) {
        return notify_fail("你正在戰鬥，沒辦法從容的進食...\n");
    }

    if( !ob->stuff_ob(me) ) {
        return 1;
	}
	
    message_vision("$N吃下了一" + ob->query("unit") + "$n。\n", me, ob);
    
    ob->add_amount(-1);
    if( ob->query_amount() <= 0 ) destruct(ob);

    return 1;
}

int help()
{
    write(@TEXT
指令格式：eat <食物>

這個指令用來讓你的人物進食或服用藥物。
TEXT);
    return 1;
}
