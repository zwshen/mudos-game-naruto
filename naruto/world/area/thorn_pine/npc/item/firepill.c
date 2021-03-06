#include <ansi.h>

inherit ITEM;

int do_firepill(object obj);

void create()
{
    set_name(HIR"炸藥"NOR, ({ "firepill" }));
    set_weight(100);
    if( !clonep() ) {
        set("unit", "綑");
        set("value", 400);
        set("long", "一綑綁起來的爆竹，稍有威力。可以丟(throw)");
    }
    setup();
}
void init()
{
    add_action("do_throw", "throw");
}
int do_throw(string arg)
{
    string func,target;
    object ob;

    if( this_player()->is_busy())
        return notify_fail("你正在忙碌中。\n");

    if( !this_player()->is_fighting() )
        return notify_fail("你沒在戰鬥。\n");

    if( !arg || sscanf(arg, "%s %s", func, target)!=2 )
        return notify_fail("你想用什麼丟誰？\n");

    if( !objectp(ob = present(target, environment(this_player()))) )
        return notify_fail("這裡沒有你要丟的目標。\n");

    if( !ob || !ob->is_character() || ob->is_corpse() || ob == this_player() )
        return notify_fail("你只需赤手空拳就能對付他了。\n"NOR);

    if( userp(ob) ) return notify_fail("不能對玩家使用。\n");  // add by -Acme-
    if( func == "firepill") {
        do_firepill(ob);
        return 1;
    }
    return 0;
}
int do_firepill(object ob)
{
    object me;
    int damage, exact, evade;

    me = this_player();
    exact = me->query_level();
    evade = ob->query_level();

    me->add_temp("apply/attack", 50);
    damage = COMBAT_D->isDamage(me, ob, 0);
    me->add_temp("apply/attack", -50);

    if( damage < 20 ) damage = random(20);

    message_vision("\n$N拿起"HIR"炸藥"NOR"快速丟向$n！\n"NOR, me, ob);
    if( !COMBAT_D->SkillHit(me, ob, exact, evade) ) {
        message_vision(" $n從旁邊避開了。\n\n", me, ob);
        destruct(this_object());
    } else {
        message_vision( sprintf("「霹靂啪啦」聲響起，$n被炸傷了。(%d) %s\n\n", damage, COMBAT_D->report_status(ob) ), me, ob);
        ob->damage_stat("hp", damage, ob);
        destruct(this_object());
    }
    me->start_busy(2);
    return 1;
}
