/*  order.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int res;
    object ob;
    string who, cmd, verb, path;

    if( me != this_player(1) ) return 0;

    if( me->is_busy() ) return notify_fail("你現在沒有空。\n");

    if( !arg || arg=="" || sscanf(arg, "%s to %s", who, cmd)!=2 )
        return notify_fail("你要命令誰做什麼事﹖\n");

    if( who == "_MY_PET_" ) {
    	if( !objectp(ob = me->query_temp("pet")) ) 
    		return notify_fail("你似乎沒有忍犬...\n");
    } else {
        ob = present(who, environment(me));
        if( !ob || !ob->is_character())
            return notify_fail("這裡沒有這個人。\n");
    }

    if( sscanf(cmd, "%s %*s", verb) != 2 ) verb = cmd;

    if( stringp(path = ob->find_command(verb)) && path != "/cmds/std/" + verb )
        return notify_fail("你不能命令別人做這種事。\n");

    if( wizardp(ob) && wiz_level(me) <= wiz_level(ob) )
        return notify_fail("你不能指揮這個人。\n");

    write("你命令" + ob->name() + ": " + cmd + "\n");
    if( (object)ob->query_owner() != me || !ob->accept_order(me, verb) )
        return notify_fail( "看起來" + ob->name() + "並不想聽你指揮。\n");

    me->start_busy(2);

    notify_fail( ob->name() + "無法完成這個命令。\n");
    seteuid(getuid());
    res = ob->force_me(cmd);
    return res;
}

int help(object me)
{
    write(@TEXT
指令格式﹕order <某人> to <指令>

命令他人執行某個指令。
如果要命令自已的忍犬，可直接使用 _MY_PET_ 而不需要使用忍
犬的id，以免在同一格太多忍犬而發生錯亂。
例：order _MY_PET_ to say hi
TEXT
    );
    return 1;
}
