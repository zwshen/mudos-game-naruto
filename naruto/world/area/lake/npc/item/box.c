#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name("傳家之寶", ({ "house box", "box" }));
    if( !clonep() ) {
        set("base_unit", "個");
        set("unit", "個");
        set("base_value", 50);
        set("base_weight", 100);
        set("no_box", 1);
        set("long", "破舊的寶箱，上面貼滿了封條完全無法打開(use)。");
    }
    setup();
}
int do_use(object me)
{
    object item;
    if( me->query_temp("quest/applaudbox") == 2) {
        message_vision("$N雙手觸碰$n的同時，$n突然搖晃了起來！\n", me, this_object());
        message_vision("只見箱子將$N手上的藍色紋路吸入箱內，同時發出一陣驚人的強光。\n", me);
        me->delete_temp("quest/applaudbox");
        if( file_size(__DIR__"bell.c") < 0 ) return 0;
        if( catch(item = new(__DIR__"bell.c")) ) return 0;
        if( item->move(me) ) {
            message_vision("\n四周傳出美妙的鐘聲，只見強光中一尊刺眼的"+item->name()+"緩緩落至$N手中。\n", me, this_object());
            destruct(this_object());
            return 1;
        } else
        if( item->move(environment(me)) ) {
            message_vision("\n四周傳出美妙的鐘聲，只見強光中一尊刺眼的"+item->name()+"緩緩落在地上。\n", me, this_object());
            destruct(this_object());
            return 1;
        }
        me->delete_temp("quest/applaudbox");
        destruct(item);
        destruct(this_object());
        return 0;
    }
    message_vision("$N用力扯開$n，但是失敗了。\n", me, this_object());
    return 1;
}
