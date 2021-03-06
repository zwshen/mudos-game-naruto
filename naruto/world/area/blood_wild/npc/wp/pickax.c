#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("十字鎬", ({ "pickax" }));
    set_weight(15000);
    setup_weapon(15, 25, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 2000);
        set("long", "鐵製的工具，可以用來挖掘(digging)土質較鬆軟的岩壁，通常被用在\n"
                    "採礦、移山等等的粗重工作上。不想挖可以停止(giveup)。\n" );
    }
    setup();
}
void init()
{
    if( environment(this_object()) && userp(environment(this_object())) ) {
        add_action("do_digging", "digging");
        add_action("do_giveup", "giveup");
    }
}

int do_giveup(string arg)
{
    if( !this_player()->query_temp("is_digging") ) return notify_fail("你沒有在挖礦。\n");
    tell_object(this_player(), "你決定停止挖礦。\n");
    this_player()->delete_temp("is_digging");
    this_player()->start_busy(1);
    return 1;
}

int do_digging(string arg)
{
    int delay;
    object env, me = this_player();

    if( !objectp(env = environment(me)) ) return 0;

    if( !this_object()->query("equipped") ) return notify_fail("沒有裝備十字鎬怎麼挖礦！\n");
    if( me->query_temp("weapon/twohanded") != this_object() ) return notify_fail("沒有裝備十字鎬怎麼挖礦！\n");
    if( me->query_temp("is_digging") ) return notify_fail("你已經在挖礦了。\n");
    if( me->is_fighting() || me->is_busy() ) return notify_fail("你太忙了，無法分心挖礦。\n");

    if( env->is_area() ) {
        int x, y;
        x = me->query("area_info/x_axis");
        y = me->query("area_info/y_axis");
        if( !env->query_data(x, y, "dig") ) return notify_fail("這個位置是不能挖礦的！\n");
    } else {
        if( !env->query("dig") ) return notify_fail("這個位置是不能挖礦的！\n");
    }
    switch( random(4) ) {
        case 0:
            message_vision(CYN"$N將袖子捲了起來，揮舞著沉重的"+query("name")+"叮叮噹噹敲打著岩壁...\n"NOR,me);
            break;
        case 1:
            message_vision(CYN"$N在雙手各吐了一口口水磨擦幾下，準備盡全力挖掘岩壁...\n"NOR,me);
            break;
        case 2:
            message_vision(CYN"$N敲敲岩壁，終於選定了一個最脆弱的點舉起"+query("name")+"開始挖掘...\n"NOR,me);
            break;
        default:
            message_vision(CYN"$N將"+query("name")+"扛在肩上，忽然一股作氣朝岩壁上用力劈了下去...\n"NOR,me);
            break;
    }
    me->set_temp("is_digging", 1);

    delay = 5 + random(16);

    me->start_busy(delay);

    // 進入挖礦 function
    call_out("digging_2", delay, me);
    return 1;
}

int digging_2(object me)
{
    int x=0, y=0, i, delay;
    object mob, env;

    i = random(101);

    if( !me ) return 1;
    if( !me->query_temp("is_digging") ) return do_giveup("");
    if( !this_object()->query("equipped") ) return do_giveup("");
    if( me->query_temp("weapon/twohanded") != this_object() ) return do_giveup("");
    if( !objectp(env = environment(me)) ) return do_giveup("");
    if( me->is_fighting() ) return do_giveup("");
    if( env->is_area() ) {
        x = me->query("area_info/x_axis");
        y = me->query("area_info/y_axis");
        if( !env->query_data(x, y, "dig") ) return do_giveup("");
    } else {
        if( !env->query("dig") ) return do_giveup("");
    }
    if( i > 5 && i < 16 ) {
        message_vision(CYN"$N不小心將"+this_object()->query("name")+"挖斷了！\n"NOR, me);
        mob = new("/world/area/blood_wild/npc/item/unknown.c");
        mob->set_name("斷掉的"+this_object()->query("name"), ({ "pickax" }));
        this_object()->unequip();
        move_side(mob, me);
        me->start_busy(5);
        me->delete_temp("is_digging");
        destruct(this_object());
        return 1;
    } else if( i > 20 && i < 41 ) {
        message_vision("$N挖到了煤礦。\n"NOR, me);
        mob = new("/world/area/old_forest/item/coal.c");
        delay = 5 + random(6);
        if( !mob->move(me) ) move_side(mob, me);
    } else if( i > 70 && i < 81 ) {
        message_vision("$N挖到了銅礦。\n"NOR, me);
        mob = new("/world/area/old_forest/item/copper.c");
        delay = 5 + random(6);
        if( !mob->move(me) ) move_side(mob, me);
    } else if( i > 95 && i < 101 ) {
        message_vision("$N挖到了鐵礦。\n"NOR, me);
        mob = new("/world/area/old_forest/item/iron.c");
        delay = 5 + random(6);
        if( !mob->move(me) ) move_side(mob, me);
    } else if( i == 3 || i == 18 || i == 40 || i == 55 || i == 83 ) {
        message_vision(CYN"結果岩壁發出怒吼開始攻擊$N！原來是挖到了沉睡中的魔人！\n"NOR, me);
        mob = new("/world/area/blood_wild/npc/monster.c");
        if( !area_move(environment(me), mob, x, y) ) {
            destruct(mob);
        } else {
            mob->kill_ob(me);
            if( function_exists("accept_kill", me) && !me->is_killing(mob) && me->accept_kill(mob) ) return 1;
            if( !me->is_killing(mob) ) me->kill_ob(mob);
        }
        me->delete_temp("is_digging");
        return 1;
    } else {
        delay = 5 + random(16);
    }
    call_out("digging_2", delay, me);
    me->start_busy(delay);
    return 1;
}
