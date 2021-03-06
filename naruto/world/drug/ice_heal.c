#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name(HIC"冰鎮"HIY"甜粥"NOR, ({ "Ice porridge", "ice", "porridge" }));
    set("unit", "大碗");
    set("base_unit", "大碗");
    set("base_value", -1);
    set("base_weight", 200);
    set("no_box", 1);
    set("food_stuff", 30);    // 食物量，食品一定要有食物量
    set("long", "藥大師的秘方所製成，不斷地散出微弱的寒氣，是一碗能去火消暑，\n"
                "還能消除全身疲勞的極品良藥，因為成功完成這種甜粥的人少之又少\n"
                "所以就算商人也怕買到假藥而不敢收購。\n"
             HIW"使用方法為"HIC"(use ice)"HIW"，效果是精神"HIR"MAX"HIW"。\n"NOR);
    setup();
}

void do_use(object me)
{
    if( environment(this_object()) != me ) {
        write("這東西不在你身上，不能亂吃。\n");
        return;
    }
    message_vision("$N拿出一碗冒出寒氣的$n，一口氣就灌了下去。\n", me, this_object());
    message_vision(HIC"$N感到全身一陣涼意，腦中一片清醒。\n"NOR, me, this_object());
    me->heal_stat("ap", me->query_stat_maximum("ap"));
    tell_object(me,HIY"(你的精神回復了 "HIR+me->query_stat_maximum("ap")+HIY" 點。)\n"NOR);

    this_object()->add_amount(-1);
    if( !this_object()->query_amount() ) destruct(this_object());
}
