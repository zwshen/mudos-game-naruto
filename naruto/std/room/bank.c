/* bank.c write by -Acme */
#include <ansi.h>

inherit ROOM;

void init()
{
    add_action("do_withdraw", "withdraw");
    add_action("do_deposit", "deposit");
    add_action("do_outward", "outward");
}

int do_withdraw(string arg)
{
    int amount, value;
    string money;
    object money_ob, bond;

    seteuid(getuid());

    if( !arg || sscanf(arg, "%d %s", amount, money) != 2 )
        return notify_fail("指令格式﹕withdraw <數量> <貨幣種類>。\n");

    if( amount < 0 )
        return notify_fail("你不能提領零以下的貨幣。\n");

    if( amount > 30000) 
        return notify_fail("你不能一次領太多。\n");    

    if( file_size("obj/money/" + money + ".c") < 0 )
    return notify_fail("你要提領哪一種錢﹖\n");

    if( catch(money_ob = new("/obj/money/" + money)) ) return 0;

    money_ob->set_amount(amount);
    value = money_ob->value();
    if( this_player()->query("bank") < value ) {
        destruct(money_ob);
        return notify_fail("你的戶頭裡沒有這麼多錢。\n");
    }

    if( !money_ob->move(this_player()) ) {
        destruct(money_ob);
        return notify_fail("你身上帶不了這許\多錢﹐提少一點吧。\n");
    }

    // 從帳戶扣錢
    this_player()->add("bank", -value);

    write("你從銀行提出" + chinese_number(amount) + money_ob->query("unit") + money_ob->name() + "。\n");

    return 1;
}

int do_deposit(string arg)
{
    int amount;
    string money;
    object money_ob;

    seteuid(getuid());

    if( !arg || sscanf(arg, "%d %s", amount, money) != 2 )
        return notify_fail("指令格式﹕deposit <數量> <貨幣種類>。\n");

    if( amount < 0 )
        return notify_fail("你不能存入零以下的錢幣。\n");
        
    if( !money_ob = present(money + "_money", this_player()) )
        return notify_fail("你身上沒有這種錢幣。\n");

    if( money_ob->query_amount() < amount )
        return notify_fail("你身上沒有這麼多的" + money_ob->name() + "。\n");

    write("你將" + chinese_number(amount) + money_ob->query("unit") + money_ob->name() + "存入銀行。\n");

    // 加在銀行裡
    this_player()->add("bank", money_ob->query("base_value") * amount);

    // 身上的錢數量減少
    money_ob->add_amount( -amount );

    if( money_ob->query_amount() <= 0 ) destruct(money_ob);

    this_player()->save_autoload();
    this_player()->save();

    return 1;
}

int do_outward(string arg)
{
    int amount;
    string id;
    object target;

    if( !arg || sscanf(arg, "%s %d", id, amount) != 2 )
        return notify_fail("指令格式： outward <人物> <數量>\n");

    if( amount <= 0 ) return notify_fail("你不能匯出小於零以下的數量。\n");
    if( amount > 1000000 ) return notify_fail("你一次不能匯出超過一百萬銀兩。\n");

    if( amount > this_player()->query("bank") ) 
    return notify_fail("你銀行裡沒有這麼多的錢。\n");

    target = find_player(id);
    if( !target ) return notify_fail("線上沒有這個人....。\n");

    if( target == this_player() ) return notify_fail("你要匯給自已？\n");

    // 扣錢
    this_player()->add("bank", -amount);

    // 匯出訊息，手續費
    tell_object(this_player(), "你將 " + amount + " 兩銀子匯給了" + target->name() + "。\n");
    if( amount >= 10 ) tell_object(target, HIY"(銀行向抽走了" + this_player()->name() + "匯來的錢 10% 手續費用。)\n"NOR);

    amount = amount - (amount/10);

    // 匯入訊息
    tell_object(target, HIW+this_player()->name()+"將 " + amount + " 兩銀子匯入到你的帳戶裡頭。\n"NOR);

    // 加錢
    target->add("bank", amount);

    log_file( "static/OUTWARD", sprintf("[%s] %s outward %d to %s\n",
       ctime(time()), geteuid(this_player()), amount, geteuid(target)) );
    return 1;
}
