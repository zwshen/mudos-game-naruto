/* sell.c by -Acme-
*/
// inherit "/adm/daemons/aucd.c";

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int auc_item(object item, int value)
{
    string name;

    if( this_player()->query("level") < 20 )
        return notify_fail("你的等級不足 20 級，無法利用拍賣物品。\n");
    if( item->query("money_id") )
        return notify_fail("你要拍賣「錢」﹖\n");
    if( this_player()->query("bank") < 100 )
        return notify_fail("你的銀行裡不足100兩，無法拍賣...\n");

    if( item->query("no_sell") || item->query("no_auc") )
        return notify_fail("這樣東西不能拍賣。\n");

    if( item->query("keep_this") )
        return notify_fail("這樣東西你已經 keep 無法拍賣。\n");
    
    if( item->query("equipped") )
        return notify_fail("這樣東西你已經裝備著，無法拍賣。\n");

    name = ( item->query_amount() ? chinese_number(item->query_amount()) : "一" );
    name += ( item->query("base_unit") ? item->query("base_unit") : 
            ( item->query("unit") ? item->query("unit") : "個" ) );
    name += item->query("name");

        if( !AUC_D->do_stock(this_player(), item, value) )
        return notify_fail("拍賣商似乎不願收下這樣物品。\n");
    this_player()->add("bank",-100);

      CHANNEL_D->do_channel(
                this_player(),
                "aucc",
    "以單價" + chinese_number(value) + "兩銀子的價錢開始進行拍賣" + name + "(" +  CHINESE_D->chinese_date(time()) + ")。"

        );
    return 1;
}

int do_list_aucer(string aucer)
{
        this_player()->start_more(AUC_D->do_list(aucer));
        return 1;
}

int do_search_goods(string name)
{
    this_player()->start_more(AUC_D->do_search_goods(name));
    return 1;
}

int do_identify(int id)
{
        this_player()->start_more(AUC_D->do_identify(id));
        return 1;
}

int main(object me, string arg)
{
        int id, amount, value;
        object item;
            string *tuned_ch;

//     return notify_fail("友克鑫拍賣場目前被大蛇丸控制中，你沒辦法使用。\n");

        tuned_ch = me->link()->query("channels");
                /*      補充上 aucc 的頻道 */
        if( !pointerp(tuned_ch) ) me->link()->set("channels", ( { "aucc"  } ) );
        else if( member_array("aucc", tuned_ch)==-1 )
            me->link()->set("channels", tuned_ch + ( { "aucc"  }) );

    // 檢視所有拍賣物
    if( !arg ) return do_list_aucer(0);

    // 拍賣商品
    if( sscanf(arg, "sell %d %s value %d", amount, arg, value) == 3 ) {
        object new_item;
        if( !(item = present(arg, me)) ) return notify_fail("你想要拍賣什麼物品？\n");
        if( amount <= 0 )  return notify_fail("你想要拍賣幾個物品？\n");
        if( item->query_amount() < amount )
                return notify_fail("你身上沒有這麼多的" + item->query("name") + "。\n");

        // 相同數量
        if( amount == item->query_amount() ) return auc_item(item, value);

        if( !objectp(new_item = new(base_name(item))) )
                return notify_fail("你似乎無法拍賣這樣物品。\n");

        new_item->set_amount(amount);
        item->add_amount(-amount);

        // 無法賣出，則dest new_item, 並將原本的item amount恢復
        if( !auc_item(new_item, value) ) {
                destruct(new_item);
                item->add_amount(amount);
        }

        return 1;
    }

    if( sscanf(arg, "sell %s value %d", arg, value) == 2 ) {
        if( !(item = present(arg, me)) )
            return notify_fail("你想要拍賣什麼物品？\n");
        return auc_item(item, value);
    }

    // 購買商品
    if( sscanf(arg, "buy %d %d", amount, id) == 2 ) {
        AUC_D->to_sell(this_player(), id, amount);
        return 1;
    }

    if( sscanf(arg, "buy %d", id) == 1 ) {
        AUC_D->to_sell(this_player(), id, 1);
        return 1;
    }

    // 檢視個人拍賣物
    if( sscanf(arg, "?%s", arg) == 1 ) return do_list_aucer(arg);

    // 搜尋拍賣物名稱
    if( sscanf(arg, "/%s", arg) == 1 ) return do_search_goods(arg);

    // 檢視商品
    if( sscanf(arg, "%d", id) == 1 ) return do_identify(id);

    // 取回物品或金錢
    if( sscanf(arg, "take %s", arg) == 1 ) {
        if( arg == "money" ) {
            AUC_D->get_money(this_player());
            return 1;
        } else {
            if( AUC_D->get_goods(this_player(), atoi(arg)) )
                CHANNEL_D->do_channel(this_player(), "aucc", "將編號" + arg + "的商品下架。");
            return 1;
        }
    }

    return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : auc                                 列出所有正在拍賣的物品
           auc <編號>                          檢視該物品的能力

           auc ?<玩家ID>                       查詢某玩家拍賣的物品列表
                                               如： auc ?acme
           auc /<關鍵字>                       查詢某項正在拍賣的物品名稱
                                               如： auc /劍  ,  auc /blade

           auc sell <物品> value <價格>
           auc sell [數量] <物品> value <價格> 將身上的物品進行拍賣並設定價格

           auc buy <編號>
           auc buy [數量] <編號>               買下正在拍賣的某編號物品

           auc take <編號>                     取回正在拍賣的物品
           auc take money                      取回拍賣所得

拍賣物品時期為七天，七天未拍賣出去，會從主列表中移出(但還可以買)
到期後之的必需在七天內領回物品，若未領回有可能會被沒收。
要拍賣物品人物必需滿20級才行，而且每人限拍賣20樣物品。
拍賣物品必需收取100兩當作佣金。

註：目前不支援競標，價格皆為直接購買價。

HELP);
    return 1;
}
