// drop.c

#include <login.h>
inherit F_CLEAN_UP;

int do_drop(object me, object obj);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    object obj, *inv, obj2;
    int i, amount;
    string item;

    if( me->is_busy() )
        return notify_fail("你正忙著其他事﹗\n");

    if(!arg) return notify_fail("你要丟棄什麼東西﹖\n");
    if( !environment(me) ) return 0;

    if(sscanf(arg, "%d %s", amount, item)==2) {
        if( !objectp(obj = present(item, me)) )
            return notify_fail("你身上沒有這樣東西。\n");
        if( stringp(obj->query("no_drop")) || obj->query("keep_this") )
            return notify_fail("這個東西沒辦法丟棄，或是已經keep了...\n");
        if( !obj->query_amount() )
            return notify_fail( obj->name() + "不能被分開丟棄。\n");
        if( amount < 1 )
            return notify_fail("東西的數量至少是一個。\n");
        if( amount > obj->query_amount() )
            return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
        else if( amount == (int)obj->query_amount() )
            return do_drop(me, obj);
        else {
            obj->set_amount( (int)obj->query_amount() - amount );
            seteuid(MUDLIB_UID);
            obj2 = new(base_name(obj));
            seteuid(getuid());
            obj2->set_amount(amount);
            return do_drop(me, obj2);
        }
    }

    if(arg=="all") {
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++) {
            do_drop(me, inv[i]);
        }
        write("Ok.\n");
        return 1;
    }

    if(!objectp(obj = present(arg, me)))
        return notify_fail("你身上沒有這樣東西。\n");
    return do_drop(me, obj);
}

int do_drop(object me, object obj)
{
    mixed no_drop;

    if( no_drop = obj->query("no_drop") )
        return notify_fail( stringp(no_drop) ? no_drop : "這樣東西不能隨意丟棄。\n");

    if( obj->query("keep_this") ) 
    return notify_fail("這樣東西你已經 keep 無法丟棄。\n");
    
    if( obj->query("equipped") )
    return notify_fail("這樣東西你已經裝備著，無法丟棄。\n");

    if( environment(me)->is_area() ) {
        if( environment(me)->query("no_drop") ) {
            if( !function_exists("query_amount", obj) ) message_vision( "$N丟下的一" + obj->query("unit") + "$n化為一陣煙霧，消失在這裡。\n", me, obj);
            else message_vision( "$N丟下的" + chinese_number(obj->query_amount()) + obj->query("unit") + "$n化為一陣煙霧，消失在這裡。\n", me, obj);
            destruct(obj);
            return 1;
        }
        if( !area_move(environment(me), obj, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) return 0;
        } else if( !obj->move(environment(me)) ) return 0;

    // add log by -Acme-
    //  if( userp(me) ) log_file("static/DROP", sprintf("%s(%s) droped %s->%O\n", me->query("name"), me->query_id(), obj->query("name"), obj));

    if( obj->is_character() ) message_vision("$N將$n從背上放了下來﹐躺在地上。\n", me, obj);
    else {
        if( !function_exists("query_amount", obj) ) message_vision( "$N丟下一" + obj->query("unit") + "$n。\n", me, obj);
        else message_vision( "$N丟下" + chinese_number(obj->query_amount()) + obj->query("unit") + "$n。\n", me, obj);

        if( !obj->query("value") && !obj->value() ) {
            write("因為這樣東西並不值錢﹐所以人們並不會注意到它的存在。\n");
            destruct(obj);
            return 1;
        }
    }
    // 不值錢的東西早就被 dest 掉了... 這裡沒有 obj.... -elon 12/2/96
    if( obj ) obj->delete("keep_this");

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : drop <物品名稱>
 
這個指令可以讓你丟下你所攜帶的物品.
例如:
drop all丟下所有未 keep 的物品.
drop sword 2丟下你所攜帶的第二把 sword.
drop 200 gold丟下二百兩黃金. 
HELP
    );
    return 1;
}
