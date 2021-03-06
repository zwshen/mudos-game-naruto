/* food.c
   標準食物持續恢復 ap, hp, mp 物件

   資料結構
   ([ "duration": 時效,
   	  "ap": 療效,
   	  "hp": 療效,
   	  "mp": 療效
   ])
*/
#include <ansi.h>

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("food");
}

void condition_update(object me, string cnd, mixed cnd_data)
{
    int heal;
    
    if( !living(me) ) return;
    
    // 在戰鬥中或是時效到了，則移到效果
    if( !mapp(cnd_data) || (cnd_data["duration"]--) < 1 || me->is_fighting() ) {
        tell_object(me, "你已經結束了進食...\n");
        me->delete_condition(cnd);
        return;
    }

    // 恢復AP值
    heal = cnd_data["heal_ap"];
    me->heal_stat("ap", heal);

    // 恢復HP值
    heal = cnd_data["heal_hp"];
    me->heal_stat("hp", heal);

    // 恢復MP值
    heal = cnd_data["heal_mp"];
    me->heal_stat("mp", heal);
    
    // 進食中不能動
    me->start_busy(2);
}

/*
void condition_apply(object me, string cnd, mapping cnd_data)
{
    cnd_data["name"] = HIG"進食中"NOR;
    me->set_condition(cnd, cnd_data);
}
*/
/*
void condition_apply(object me, string cnd, mapping cnd_data) { }
void condition_unapply(object me, string cnd, mapping cnd_data) { }
*/
