// 卡莉法的泡泡果實-黃金泡沫效果

#include <ansi.h>
inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("golden_bubble");
}

// 每 update 一次 判斷是不是還在戰鬥，不是就解除
void condition_update(object me, string cnd, mixed cnd_data)
{
    mapping weapons;
    string skill;
    object ob;

    if( !me->is_fighting() ) {
        message_vision(HIC"$N"NOR+HIC"好不容易逃離了戰鬥，立刻找水將泡泡洗掉。\n"NOR, me);
        me->delete("no_defend");
        me->delete("no_combat");
        me->delete_condition("golden_bubble");
        return;
    }
    // 用心跳判斷武器
    if( me->query_condition("golden_bubble") != 0 && mapp(weapons = me->query_temp("weapon")) && sizeof(weapons) ) {
        foreach(skill, ob in weapons) ob->unequip();
    }
    me->set("no_defend", 1);      // 不能防禦
    me->set("no_combat", 1);      // 不能攻擊
}
void condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( cnd != "golden_bubble" ) return;
    if( !cnd_data ) cnd_data = me->query_condition("golden_bubble");
    if( !cnd_data ) return;

    me->delete("no_defend");
    me->delete("no_combat");
}
