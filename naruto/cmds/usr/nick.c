/*  nick.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    if( !arg ) return notify_fail("你要替自己取什麼綽號﹖\n");

    arg = color(arg);

    if( strlen(uncolor(arg)) > 14 )
	    return notify_fail("你的綽號太長了﹐想一個短一點的、響亮一點的。\n");

    seteuid(getuid());
    me->set("nickname", arg);    // use arg + NOR if colorful nick is open
    write("Ok。\n");
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : nick <外號, 綽號>
 
這個指令可以讓你為自己取一個響亮的名號或頭銜。
綽號可以使用 ANSI 顏色控制碼，請輸入 help ansi
HELP);
        return 1;
}
