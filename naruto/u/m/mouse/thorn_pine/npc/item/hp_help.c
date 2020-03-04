#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("體力急救", ({ "hp help", "help" }));
    set_weight(100);
    if( !clonep() ) {
        set("unit", "包");
        set("value", 2000);
        set("long", "戰鬥中急救專用，以(use)使用。");
    }
    setup();
}
void do_use(object me)
{
    if( !this_player()->is_fighting() ) {
        write(CYN"沒在戰鬥吃什麼急救包。"NOR"\n");
        return;
    }
    message_vision("$N打開$n將裡面的藥品快速吞了下去。好像回復少許體力\n", me, this_object());
    me->heal_stat("hp", 100);
    destruct(this_object());
}
