#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(RED"辣椒丸"NOR, ({ "chili pill", "pill" }));
    if( !clonep() ) {
        set("unit", "顆");
        set("value", 0);
        set("base_value", 0);
        set("base_weight", 1);
        set("no_box", 1);
        set("long","秋道一族的秘藥，外表火紅，光看就覺得非常辛辣。\n");
    }
    setup();
}

void do_use(object me, string arg)
{
    mapping cnd = ([]);
    object *inv, item;
    int sk, add;

    inv = all_inventory(me);

    if( me->is_busy() ) {
        write("你正在忙碌，沒空吃藥。\n");
        return;
    }
    if( me->query_attr("con") < 70 ) {
        write("你的體格無法負擔秋道秘藥。\n");
        return;
    }
    if( me->query_condition("akimichi1") != 0 ) {
        write("你已經吃過秋道秘藥了，等時效過了再吃吧。\n");
        return;
    }
    if( me->query_condition("akimichi2") != 0 ) {
        write("辣椒丸正在發揮效用中，再吃第二顆可能會喪命。\n");
        return;
    }
    if( me->query_condition("akimichi3") != 0 ) {
        write("辛辣感還沒退去前不能再吃藥。\n");
        return;
    }
    foreach(item in inv) {
        if( item->query("equipped") ) {
            write("吃下秋道秘藥時身體會散發熱氣，因此不能穿著任何裝備。\n");
            return;
        }
    }
    sk = me->query_skill("akimichi pill");

    if( sk < 40 ) {
        write("你的秋道秘藥知識不足，不知道如何食用才會有效果。\n");
        return;
    }
    add = me->query_stat("ap") + me->query_stat("hp");

    message_vision("\n$N將$n丟入口中大口咀嚼著，只見$N臉色快速變紅，似乎快要爆發了。\n"NOR, me, this_object());
    tell_object(me,HIR"辣椒丸的效果逐漸顯現，你感覺力量與查克拉源源不絕湧現！\n"NOR);

    cnd["name"] = RED"辣椒丸"NOR;
    cnd["duration"] = sk;
    cnd["attack"] = sk/2;
    cnd["armor"] = sk/2;
    cnd["mp"] = add;

    me->set_condition("akimichi2", cnd);
    me->set_stat_current("hp", 1);
    me->set_stat_current("ap", 1);
    me->heal_stat("mp", add);
    me->improve_skill("akimichi medicine", 1);
    me->start_busy(2);

    // 個數減少
    this_object()->add_amount(-1);
    if( !this_object()->query_amount() )
        destruct(this_object());
}
