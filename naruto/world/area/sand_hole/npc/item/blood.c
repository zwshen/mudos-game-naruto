#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name("蠍毒"HIR"血清"NOR, ({ "blood serum", "serum" }));
    if( !clonep() ) {
        set("unit", "瓶");
        set("value", 0);
        set("no_sell", 1);
        set("base_value", 0);
        set("base_weight", 1);
        set("long","能解除蠍毒的血清，使用方法為 use serum。\n");
    }
    setup();
}

void do_use(object me, string arg)
{
    if( me->query_condition("scorpion_poison") == 0 ) {
        write("你目前沒有中蠍毒，隨便使用血清只會造成負擔。\n");
        return;
    }
    message_vision("$N打開了$n，將血清注入到身上，臉色看起來好多了。\n"NOR, me, this_object());

    me->start_busy(1);
    me->delete_condition("scorpion_poison");

    // 個數減少
    this_object()->add_amount(-1);
    if( !this_object()->query_amount() )
        destruct(this_object());
}
