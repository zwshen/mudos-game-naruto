/* goto.c */
#include <command.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int x, y;
    string file, out_msg, in_msg;
    object obj;

    SECURED_COMMAND;

    if( !arg ) return notify_fail("你要去哪裡﹖\n");

    if( sscanf(arg, "goto_out_msg %s", out_msg) == 1 ) {
    	me->set("goto_out_msg", color(out_msg));
    	write("Ok.\n");
    	return 1;
    } else if( sscanf(arg, "goto_in_msg %s", in_msg ) == 1 ) {
    	me->set("goto_in_msg", color(in_msg));
    	write("Ok.\n");
    	return 1;
    }

    if( me->query("goto_out_msg") ) out_msg = me->query("goto_out_msg") + "\n";
    else out_msg = "只見一陣煙霧過後，$N的身影已經不見了。\n";

    if( me->query("goto_in_msg") ) in_msg = me->query("goto_in_msg") + "\n";
    else in_msg = "只見一陣煙霧過後，$N的身影已經來到了這裡。\n";

    // goto 到區域 by -Acme-
    if( sscanf(arg, "%s %d %d", file, x, y) == 3 ) {
        file = resolve_path(me->query("cwd"), file);
        if( !sscanf(file, "%*s.c") ) file += ".c";
        if( file_size(file) >=0 && (obj=load_object(file)) ) {
			if( !obj->is_area() ) return 1;
	    	message_vision(out_msg, me);
			area_move(obj, me, x, y);
		    message_vision(in_msg, me);
		    return 1;
        } else {
        	write("這個區域檔不存在。\n");
        	return 1;
        }
        
    // 自已身處域區的座標goto
    } else if( sscanf(arg, "%d %d", x, y) == 2 ) {
    	if( !environment(me)->is_area() ) return 1;
    	message_vision(out_msg, me);
		area_move(environment(me), me, x, y);
	    message_vision(in_msg, me);
   		return 1;
    }

    obj = find_player(arg);
    if( !obj ) obj = find_living(arg);
    if( obj == me ) {
    	write("你要移到自已身旁？\n");
    	return 1;
    }

    // 移到一般房間
    if( !obj || !obj->visible(me)) {
        arg = resolve_path(me->query("cwd"), arg);
        if( !sscanf(arg, "%*s.c") ) arg += ".c";
        if( file_size(arg) >=0 && (obj=load_object(arg)) ) {
            if( obj->is_area() ) {
            	write("移動到區域物件，必需加上座標才能移動。\n");
            	return 1;
            }
   	        message_vision(out_msg, me);
            me->move(obj);
   	        message_vision(in_msg, me);
    		return 1;
        } else return notify_fail("沒有這個玩家、生物、或地方。\n");
    }

    if( !environment(obj) ) return notify_fail("這個物件沒有環境可以 goto。\n");

    if( environment(obj)->is_area() ) {
    	if( area_environment(obj, me) ) return notify_fail("你已經在他身旁了。\n");

        message_vision(out_msg, me);
		if( !area_move(environment(obj), me, obj->query("area_info/x_axis"), obj->query("area_info/y_axis")) ) {
            tell_object(me, "因為某種理由，你的 goto 失敗了。\n");
		}
    } else {
        message_vision(out_msg, me);
        if( !me->move(environment(obj)) ) {
            tell_object(me, "因為某種理由，你的 goto 失敗了。\n");
        }
    }

    message_vision(in_msg, me);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : goto <目標>
 
這個指令會將你傳送到指定的目標。目標可以是一個living 或房間
的檔名。如果目標是living，你會被移到跟那個人同樣的環境。

你可以自行設定goto的離開訊息，或是goto的進來訊息。
如： goto goto_out_msg $HIW$你可以聽到$N哇哈哈的一聲，離開了這裡。
     goto goto_in_msg  $HIW$你可以聽到$N哇哈哈的一聲，來到了這裡。
使用色碼系統在最後會自動加上$NOR$所以可以不需要再加一次。
HELP);
    return 1;
}
