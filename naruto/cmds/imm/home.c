// home.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string id, msg;
	object home;

    id = me->query_id();
    
    if( arg ) {
    	if( !objectp( home = load_object("/u/" + arg[0..0] + "/" + arg + "/workroom.c") ) ) {
    		write(arg + "的工作目錄下沒有workroom的存在，你無法移動。\n");
    		return 1;
    	}
		message_vision("$N向眾人揮揮手，到" + arg + "家串門子去。\n", me);
		if( me->move(home) )
			message("tell_room", "一陣輕煙過去後，" + me->name() + "來到了這裡。\n", environment(me), me);
		return 1;
    }

	if( !objectp( home = load_object("/u/" + id[0..0] + "/" + id + "/workroom.c") ) ) {
		message_vision("$N向眾人揮揮手，回家去了。\n", me);
		me->move("/world/area/wizard/guildhall");
		message("tell_room", me->name() + "回到了自己的家中。\n", environment(me), me);
		return 1;
	}

	if( stringp(msg = me->query("env/msg_home")) )
		message_vision(msg + "\n", me);
	else
		message_vision("$N向眾人揮揮手，回家去了。\n", me);
	me->move(home);
	message("tell_room", me->name() + "回到了自己的家中。\n", environment(me), me);
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : home [id]

利用此一指令可直接回到自己的工作室或別的巫師的工作室，若 home directory 中
無 workroom.c 檔，則回到 wiz guild。如果你 workroom.c 中有 'msg_home' 這個
設定, 則在場的人都會看到那個訊息。
HELP
    );
    return 1;
}
