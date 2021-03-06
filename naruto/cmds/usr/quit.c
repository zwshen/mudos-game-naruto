/* quit.c */

#include <command.h>
#include <login.h>
#include <action.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
    seteuid(getuid());
    set("channel_id", "離線指令");
}

int main(object me, string arg)
{
    int i;
    object link_ob, ob, ob2;

    if( !userp(me) ) return 0;
    if( me->is_busy() && arg != "!" ) {
        write("你正忙著呢, 請試著停下所忙的事。\n");
        return 1;
    }

    if( me->query_team() ) me->dismiss_team();

    // 檢查身上是否有袋子，若有，將袋子裡的東西移到身上
    foreach(ob in all_inventory(me))
        if( ob->accept_object() ) // 是個袋子
            foreach(ob2 in all_inventory(ob))
            	if( !ob2->move(me) ) DROP_CMD->do_drop(me, ob2);

    link_ob = me->link();

    // We might be called on a link_dead player, so check this.
    if( link_ob ) {

        // Are we possessing in others body ?
        if( link_ob->is_character() ) {
            write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
            exec(link_ob, me);
            link_ob->setup();
            return 1;
        }

        link_ob->set("last_on", time());
        link_ob->set("last_from", query_ip_name(me));
#ifdef SAVE_USER
        link_ob->save();
#endif
        destruct(link_ob);
    }

    // 設定連線進入開始位置
    if( environment(me) && !environment(me)->query("void") && !environment(me)->is_character() )
		me->set("startroom", file_name(environment(me)) );

    // if pking, set a pker mark before quit -dragoon
    if( time() - (int)me->query("last_pk_time") < 60 * 60 ) me->set("pker", 1);

    write("歡迎下次再來﹗\n");
    message_vision("$N(" + me->query("id") + ") 離開遊戲。\n", me);
//    message("system", me->name() + "(" + me->query("id") + ") 離開遊戲。\n", environment(me), me);

    CHANNEL_D->do_channel(this_object(), "sys",    me->name() + "("+ me->query("id") +") 離開遊戲了。");

#ifdef SAVE_USER
    me->save();
    if( objectp(me->query_temp("pet")) ) me->query_temp("pet")->save();
#endif
    log_file( "USAGE", sprintf("[%s] %12s quit\n", ctime(time()), (string)me->query("id")));

    if( objectp(me->query_temp("pet")) ) destruct(me->query_temp("pet"));
    destruct(me);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : quit

當你(妳)想暫時離開時, 可利用此一指令。
HELP
    );
    return 1;
}
