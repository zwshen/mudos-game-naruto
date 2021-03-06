#include <ansi.h>

inherit AREA;

void create()
{
    set("name", "死亡碉堡");
    set("x_axis_size", 49);            // 橫向大小
    set("y_axis_size", 49);            // 縱向大小
    setup();
    set("no_recall", 1);
}

void init()
{
    add_action("do_scale", "scale");
    add_action("do_pass", "pass");
}

int do_scale(string arg)
{
    int x, y, i;
    object me, dolomite, area;
    string area_file = "/world/area/lv60_area/deadcity.c";
    me = this_player();

    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;

    if( !userp(me) || x != 24 || y != 36 ) return 0;
    if( me->query_temp("dolomite_ok") ) {
        message_vision(CYN"天枰後方的門發現了$N後，立刻發出彩光將$N吸了進去。\n"NOR, me);
        if( !area_move(area, me, 27, 25) ) return 0;
        return 1;
    }
    if( userp(me) && !me->query("dolomite_amount") ) me->set("dolomite_amount", 150+random(450));

    i = me->query("dolomite_amount");

    if( objectp(dolomite = present("_DOLOMITE_", me)) ) {
        if( me->query("dolomite_amount") <= dolomite->query_amount() ) {
            message_vision("$N拿出了"+chinese_number(i)+"堆石灰放在天枰上。\n"NOR, me);
            message_vision(CYN"\n重量似乎剛好，天枰持平後往前一挪，後面的門打開一道小縫忽然將空氣吸入！\n$N因為站的太近，和天枰上的石灰一起被吸入，失去平衡的天枰又回復成原狀。\n\n"NOR, me);
            if( !area_move(area, me, 27, 25) ) return 0;
            dolomite->add_amount(-i);
            if( !dolomite->query_amount() ) destruct(dolomite);
            me->delete("dolomite_amount");
            if( me->query_level() < 41 ) me->set_temp("dolomite_ok", 1);
            else if( me->query_temp("dolomite_ok") ) me->delete_temp("dolomite_ok");
        } else {
            i = me->query("dolomite_amount") - dolomite->query_amount();
            tell_object(me, "總共還少了"+chinese_number(i)+"堆石灰，等集齊再一次放吧。\n"NOR);
        }
        return 1;
    }
    tell_object(this_player(),"天枰上浮現出數字 "HIY+i+NOR" 但不知道是什麼意思。\n"NOR);
    return 1;
}

int do_pass(string arg)
{
    object me, area;
    string area_file = "/world/area/muye/deadforest.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "密林" ) return 0;
    if( me->query("area_info/x_axis") != 24 || me->query("area_info/y_axis") != 0 ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N努力地將身體擠進空間不大的樹林中。\n", me);
    if( !area_move(area, me, 46, 48) ) return 0;
    message_vision("$N好不容易才擠了進來。\n", me);
    return 1;
}
