/* mpheal1.c 
   狀態 mp 之恢復效能，恢復量是固定值

   資料結構
   ([ "duration": 時效 ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("mpheal1");
}

void condition_update(object me, string cnd, mixed cnd_data)
{
    if( !living(me) ) return;
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 ) {
        me->delete_condition(cnd);
        return;
    }

    // 恢復MP值
    me->heal_stat("mp", 10);
}


void food_condition_apply(object me, mapping cnd_data)
{
    mapping mpheal;
    
    if( !mapp(mpheal = me->query_condition("mpheal1")) )
        mpheal = ([]);
    
    mpheal["duration"] += cnd_data["duration"];
    mpheal["name"] = BMAG"Ｃ級天地術"NOR;
    
    if( mpheal["duration"] <= 0 ) mpheal["duration"] = 1;
    else if( mpheal["duration"] > 200 ) mpheal["duration"] = 200;
    
    me->set_condition("mpheal1", mpheal);
}

/*
void condition_apply(object me, string cnd, mapping cnd_data) { }
void condition_unapply(object me, string cnd, mapping cnd_data) { }
*/
