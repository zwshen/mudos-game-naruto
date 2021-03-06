#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(GRN"蛇皮繃帶"NOR, ({ "snake-skin bandage", "bandage" }));
    set_weight(1);
    if( !clonep() ) {
        set("base_unit", "條");
        set("unit", "條");
        set("base_value", 10);
        set("base_weight", 10);
        set("long", "一個用來急救的繃帶。\n"
                    "效果：馬上恢復 100 hp\n"
                    "使用方式：use bandage          對自已急救\n"
                    "          use bandage on <id>  對某人急救\n" );
    }

    setup();
}

void do_use(object me, string arg)
{
    object who;
    mapping condition;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空。\n");
    }

    if( arg && arg != "" ) {
        who = present(arg, environment(me));
        if( !objectp(who) ) return notify_fail("你附近沒有這個人。\n");
    } else who = me;

    if( who->query_condition("cd_first_aid") ) {
        tell_object(me, "你現在沒有辦法對"+ who->name() +"急救。\n");
        return;
    }

    who->heal_stat("hp", 100);
    message_vision(HIW"$N使用了一條"GRN"蛇皮繃帶"NOR"馬上治療$n體力值 100 點。\n"NOR, me, who);

    condition = ([]);
    condition["duration"] = 60;
    condition["name"] = BLU"(冷卻)"HIK"急救"NOR;
    who->set_condition("cd_first_aid", condition);

    this_object()->set_amount(this_object()->query_amount()-1);
    if( this_object()->query_amount() <= 0 )
        destruct(this_object());
}
