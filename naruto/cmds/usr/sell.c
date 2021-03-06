/* sell.c by -Acme-
*/

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int sell_item(object item)
{
	int value;
    string name;

    if( item->query("money_id") )
        return notify_fail("你要賣「錢」﹖\n");

    if( item->query("no_sell") )
        return notify_fail("這樣東西不能賣。\n");

    if( (value = item->query("value")) <=0 )
        return notify_fail("這樣東西不值錢。\n");

    if( item->query("keep_this") )
    	return notify_fail("這樣東西你已經 keep 無法販賣。\n");
    
    if( item->query("equipped") )
        return notify_fail("這樣東西你已經裝備著，無法販賣。\n");

    value /= 2;

    name = ( item->query_amount() ? chinese_number(item->query_amount()) : "一" );
    name += ( item->query("base_unit") ? item->query("base_unit") : 
            ( item->query("unit") ? item->query("unit") : "個" ) );
    name += item->query("name");

    if( !environment(this_player())->to_stock(item) )
    	return notify_fail("當舖似乎不願收下這樣物品。\n");

    message_vision("$N以" + chinese_number(value) + "兩銀子的價錢將" + name + "賣出去。\n", this_player() );
    
    // 直接將錢加到銀行裡
    this_player()->add("bank", value);

    return 1;
}

int main(object me, string arg)
{
	int amount;
	object item;

	if( !environment(me) )
	    return notify_fail("你現在身處在哪你都不知道了！\n");
	if( !environment(me)->is_hockshop() )
	    return notify_fail("你只能在當舖賣東西。\n");
    if( me->is_busy() )
        return notify_fail("你現在沒有空！\n");
    if( !arg )
    	return notify_fail("你想賣什麼東西？\n");
    
    if( arg == "all" ) {
        object *inv;
        
        inv = all_inventory(this_player());
        foreach(item in inv) {
            if( !item ) continue;
            sell_item(item);
        }
        write("Ok。\n");
        return 1;
    }

    if( sscanf(arg, "%d %s", amount, arg) == 2 ) {
    	object new_item;
    	if( !(item = present(arg, me)) )
    		return notify_fail("你想要賣斷什麼物品？\n");
    	if( amount <= 0 ) 
    		return notify_fail("你想要賣幾個物品？\n");
    	if( item->query_amount() < amount )
    		return notify_fail("你身上沒有這麼多的" + item->query("name") + "。\n");
    	
    	// 相同數量
    	if( amount == item->query_amount() )
    		return sell_item(item);
    	
    	if( !objectp(new_item = new(base_name(item))) )
    		return notify_fail("你似乎無法販賣這樣物品。\n");
    	
    	new_item->set_amount(amount);
    	item->add_amount(-amount);
    	
    	// 無法賣出，則dest new_item, 並將原本的item amount恢復
    	if( !sell_item(new_item) ) {
    		destruct(new_item);
    		item->add_amount(amount);
    	}
    	
    	return 1;
    }

    if( !(item = present(arg, me)) )
        return notify_fail("你想要賣斷什麼物品？\n");

    return sell_item(item);
}

int help(object me)
{
  write(@HELP
指令格式 : sell [數量] 物品

這可指令可以將你身上的物品賣出去，通常只有在當舖的地方才能夠
販賣物品。例：

sell blade     將身上的第一把刀賣出去
sell blade 2   將身上的第二把刀賣出去
sell 3 pill    將身上的pill賣出三個，通常用於「複合物品」上
sell 4 pill 2  將身上第二堆的pill賣出四個

相關指令： list, buy
HELP);
    return 1;
}
