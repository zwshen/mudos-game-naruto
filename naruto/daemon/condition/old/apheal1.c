/* apheal1.c 
   狀態 ap 之恢復效能，恢復量是固定值

   資料結構
   ([ "duration": 時效 ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("apheal1");
}

void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        me->delete_condition(cnd);
        return;
    }

    // 恢復AP值
    me->heal_stat("ap", 10);
}


void food_condition_apply(object me, mapping cnd_data)
{
    mapping apheal;
    
    if( !mapp(apheal = me->query_condition("apheal1")) )
        apheal = ([]);
    
    apheal["duration"] += cnd_data["duration"];
    apheal["name"] = BGRN"Ｃ級提神術"NOR;
    
    if( apheal["duration"] <= 0 ) apheal["duration"] = 1;
    else if( apheal["duration"] > 200 ) apheal["duration"] = 200;
    
    me->set_condition("apheal1", apheal);
}

/*
void condition_apply(object me, string cnd, mapping cnd_data) { }
void condition_unapply(object me, string cnd, mapping cnd_data) { }
*/
