/* 拍賣精靈
   write by -Acme-
*/

// #pragma save_binary
#define GOODS_MAXIMUM 1000
#define GOODS_DEADLINE 7
#define AUC_MAXIMUM 20
#define NAME "友克鑫拍賣會"

#include <ansi.h>
#include <localtime.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping goods;
mapping profit;

void create()
{
    seteuid(getuid());
//    if( !restore() && !mapp(goods) ) {
    if( !restore() ) {
        goods = ([]);
        profit = ([]);
    }
}

string query_save_file()
{
    return DATA_DIR + "aucd";
}

void do_clean()
{
    int index;

    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) break;
        if( time() > goods[index]["time"] + GOODS_DEADLINE*86400*2 )
            map_delete(goods, index);
    }
    save();
}

int do_auc_check(string id)
{
    int index, count=0;

    if( !stringp(id) ) return 0;

    if( !mapp(goods) ) {
        goods = ([]);
        profit = ([]);
        return 1;
    }

    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        if( goods[index]["aucer"] == id ) count ++;
    }
        
    if( count >= AUC_MAXIMUM ) return 0;
    else return 1;
}

int do_stock(object aucer, object item, int value)
{
    int index, amount, changed;
    string file;

    if( !objectp(aucer) || !objectp(item) ) return 0;

    if( !userp(aucer) ) return 0;

    if( value <= 0 || value > 99999999 ) return 0;

    // 不是開放的物件？
    if( base_name(item)[0..6] != "/world/" ) return 0;

    // 商品列表已滿
    if( sizeof(goods) >= GOODS_MAXIMUM ) {
        // 試著清除過期且沒人領回的物品
        do_clean();
        return 0;
    }

    if( !do_auc_check(aucer->query_id()) ) return 0;

    amount = item->query_amount();
    if( !amount ) amount = 1;

    file = base_name(item);

    // 尋找可用的商品編號
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) break;
    }

    // 編號超過當舖商品數量上限
    if( index > GOODS_MAXIMUM ) return 0;

    // 設定儲存該商品的資料
    goods[index] = ([]);
    goods[index]["file"] = file;
    goods[index]["amount"] = amount;
    goods[index]["name"] = item->query("name");
    goods[index]["id"] = item->query("id");
    goods[index]["value"] = value;

    if( item->query("wear_as") ) goods[index]["class"] = BBLU"防具"NOR;
    else if( item->query("wield_as") ) goods[index]["class"] = BRED"武器"NOR;
    else if( function_exists("stuff_ob", item) ) goods[index]["class"] = BGRN"食品"NOR;
    else goods[index]["class"] = BYEL"其它"NOR;

    if( item->query("base_unit") ) goods[index]["unit"] = item->query("base_unit");
    else if( item->query("unit") ) goods[index]["unit"] = item->query("unit");
    else goods[index]["unit"] = "個";

    goods[index]["time"] = time();
    goods[index]["aucer"] = aucer->query_id();

    // 經過修改過的物品，儲存完整的物品資料
    if( item->query("changed") ) {
        mapping dbase = item->query_entire_dbase();
        if( mapp(dbase) )
            goods[index]["dbase"] = dbase;
    }

    destruct(item);
    save();

    return 1;
}

string do_identify_msg(object obj)
{
        string msg = "";

        if( !objectp(obj) ) return msg;

    msg += obj->query("name") + "(" + obj->query("id") + ")\n\n";
    msg += obj->query("long") + "\n";

    if( obj->is_weapon() ) {
        string s;
        mapping dp, apply;
        mixed sk = obj->query("wield_as");
        
        msg += "可使用方式：\n";

        if( stringp(sk) ) sk = ({ sk });
        foreach(s in sk) {
            msg += sprintf("\n☉ %s (%s)\n", to_chinese(s), s);
            dp = obj->query("damage/" + s);

            msg += sprintf("   傷害力： %d - %d (傷害力修正 %d%%，武器等級 %d)\n", 
                dp["lower"], dp["upper"], dp["bonus"], dp["level"] );

        msg += sprintf("\n強化次數：%d/10\n", obj->query("changed"));
            apply = obj->query("apply_weapon/" + s);
            if( mapp(apply) ) {
                string prop;
                mixed value;
            
                msg += "\n   武器特性：\n";
                foreach(prop, value in apply) {
                    prop = to_chinese(prop);
                    msg += sprintf("     %-30s %O\n", prop, value);
                }
            }
        }
    } else if( obj->is_armor() ) {
        string sub_type = obj->query("wear_as");
        mapping apply = obj->query("apply_armor/" + sub_type);
        msg += sprintf("護具部位：%s\n", to_chinese(sub_type) );
        msg += sprintf("強化次數：%d/3\n", obj->query("changed"));
        if( mapp(apply) ) {
            string prop;
            mixed value;
            
            msg += "護具特性：\n";
            foreach(prop, value in apply) {
                msg += sprintf("  %-30s %O\n", to_chinese(prop), value);
            }
        }
    }

        return msg;
}

string do_identify(int index)
{
    object item;
    string msg;

    if( undefinedp(goods[index]) ) return "沒有這個商品編號。\n";

    // 無法建立該商品

    if( !objectp(item = new(goods[index]["file"])) ) {
        // 或許檔案已經不存在，從列表中刪除
        map_delete(goods, index);
        return "這個商品似乎有一點問題，被店家收了回去。\n";
    }

    // 特別的外加能力
    if( !undefinedp(goods[index]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[index]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[index]["dbase"][key[j]]);
        item->delete("equipped");
    }

    msg = "拍賣者：" + goods[index]["aucer"] + "\n拍賣物：" +  do_identify_msg(item);
    destruct(item);

    return msg;
}

string get_time(int t)
{
    mixed *local;
        string msg = "";

        if( time() > t ) msg += HIR;
    local = localtime(t);

    msg += sprintf("%d/%s/%s",
                   local[LT_YEAR],
                   local[LT_MON]+1 < 10 ? "0" + (local[LT_MON]+1) : (local[LT_MON]+1) + "",
                   local[LT_MDAY] < 10 ? "0" + local[LT_MDAY] : local[LT_MDAY] + "" );
        msg += NOR;
    return msg;
}


string do_search_goods(string key)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "目前沒有任何商品。\n";

    msg  = "╭────────────────────────────────────────╮\n";
    msg += sprintf("│%-80s│\n", NAME + "目前的商品列表" );
    msg += "├────────────────────────────────────────┤\n";
    msg += "│編號  類別  數量  單價/銀兩      到期日  名稱                                   │\n";
    msg += "├────────────────────────────────────────╯\n";
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        if( strsrch(goods[index]["name"], key) == -1 && strsrch(goods[index]["id"], key) == -1 ) continue;
        msg += sprintf("│%4d  %s%6d %10d  %s  %-s\n", 
                   index,
                   goods[index]["class"],
                   goods[index]["amount"],
                   goods[index]["value"],
                   get_time(goods[index]["time"] + GOODS_DEADLINE*86400),
                   goods[index]["name"] + "(" + goods[index]["id"] + ")" );
    }
    msg += "├────────────────────────────────────────╮\n";
    msg += "│輸入 help auc 瞭解如何使用拍賣指令。  拍賣頻道：aucc                            │\n";
    msg += "╰────────────────────────────────────────╯";
    return msg;
}

string do_list(string arg)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "目前沒有任何商品。\n";

    if( arg ) {
        msg  = "╭────────────────────────────────────────╮\n";
        msg += sprintf("│%-80s│\n", NAME + "目前的商品列表" );
        msg += "├────────────────────────────────────────┤\n";
        msg += "│編號  類別  數量  單價/銀兩      到期日  名稱                                   │\n";
        msg += "├────────────────────────────────────────╯\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
                if( goods[index]["aucer"] != arg ) continue;
            msg += sprintf("│%4d  %s%6d %10d  %s  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       get_time(goods[index]["time"] + GOODS_DEADLINE*86400),
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }
        msg += "├────────────────────────────────────────╮\n";
        msg += "│輸入 help auc 瞭解如何使用拍賣指令。  拍賣頻道：aucc                            │\n";
        msg += "╰────────────────────────────────────────╯";
    } else {
        msg  = "╭──────────────────────────────────╮\n";
        msg += sprintf("│%-68s│\n", NAME + "目前的商品列表" );
        msg += "├──────────────────────────────────┤\n";
        msg += "│編號  類別  數量  單價/銀兩  名稱                                   │\n";
        msg += "├──────────────────────────────────╯\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
//            if( time() - goods[index]["time"] > GOODS_DEADLINE*86400 ) continue;
            msg += sprintf("│%4d  %s%6d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }

        msg += "├──────────────────────────────────╮\n";
        msg += "│輸入 help auc 瞭解如何使用拍賣指令。  拍賣頻道：aucc                │\n";
        msg += "╰──────────────────────────────────╯";
    }
    
    return msg;
}

int to_sell(object who, int number, int amount)
{
    int value;
    object item;

    if( !objectp(who) ) return 0;

    // 數量檢查
    if( !amount ) amount = 1;

    if( amount <= 0 ) {
        tell_object(who, "你想要買幾個商品？\n");
        return 1;
    }

    if( amount > 999 ) {
        tell_object(who, "一次最多只能購買999個商品...\n");
        return 1;
    }

    // 沒有這個商品編號
    if( undefinedp(goods[number]) ) {
        tell_object(who, "沒有這個商品編號。\n");
        return 1;
    }

    if( goods[number]["amount"] < amount ) {
        tell_object(who, "這個商品數量沒有這麼多。\n");
        return 1;
    }
    
    value = goods[number]["value"] * amount;
    // 銀行錢不夠

    if( who->query("bank") < value ) {
        tell_object(who, "你銀行裡的錢不夠，無法購買此商品。\n");
        return 1;
    }
    
    // 無法建立該商品
    if( !objectp(item = new(goods[number]["file"])) ) {
        tell_object(who, NAME+"發現這個商品有問題後隨即下架了，你無法購買。\n");
        // 或許檔案已經不存在，從列表中刪除
        map_delete(goods, number);
        return 1;
    }
    
    if( !function_exists("set_amount", item) && amount > 1) {
        tell_object(who, "這個東西一次只能買一個。\n");
        destruct(item);
        return 1;
    }

    item->set_amount(amount);
    
    if( !undefinedp(goods[number]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[number]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[number]["dbase"][key[j]]);
        item->delete("equipped");
    }

    if( !item->move(who) ) {
        tell_object(who, NAME+"發現你似乎拿不動這樣商品，便不賣你了。\n");
        // 刪除物品
        destruct(item);
        return 1;
    }

    message_vision("$N花了" + chinese_number(value) + "兩銀子向" + NAME + "買下" +
                   chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "。\n", who);

    CHANNEL_D->do_channel( this_player(), "aucc",
        "花了" + chinese_number(value) + "兩銀子向" + NAME + "買下" +
        chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] +
        "(" +  CHINESE_D->chinese_date(time()) + ")。" );


    // 買家從銀行扣錢
    who->add("bank", -value);

    // 商品數量改變
    goods[number]["amount"] -= amount;

    // 賣家增加錢
    if( undefinedp(profit[goods[number]["aucer"]]) )
        profit[goods[number]["aucer"]] = value;
    else profit[goods[number]["aucer"]] += value;

    // 賣完了，從列表中刪除
    if( goods[number]["amount"] <= 0 ) map_delete(goods, number);
    save();

    return 1;
}

// 賣家取回錢
int get_money(object aucer)
{
        if( !objectp(aucer) || !userp(aucer) ) return 0;
        if( undefinedp(profit[aucer->query_id()]) ) return 0;
        tell_object(aucer, "你從" + NAME + "取回了" + profit[aucer->query_id()] + "銀兩，並存入銀行。\n");
        aucer->add("bank", profit[aucer->query_id()]);
        map_delete(profit, aucer->query_id());
    save();
        return 1;
}

// 賣家取回商品
int get_goods(object who, int number)
{
        object item;

    // 沒有這個商品編號
    if( undefinedp(goods[number]) ) {
        tell_object(who, "沒有這個商品編號。\n");
        return 0;
    }

    if( goods[number]["aucer"] != who->query_id() && !wizardp(who) ) {
        tell_object(who, "這件商品不是你在拍賣的。\n");
        return 0;
    }

    // 無法建立該商品
    if( !objectp(item = new(goods[number]["file"])) ) {
        tell_object(who, NAME + "發現這個商品有問題後隨即下架了，你無法取回。\n");
        // 或許檔案已經不存在，從列表中刪除
        map_delete(goods, number);
        return 0;
    }

    item->set_amount(goods[number]["amount"]);
    
    if( !undefinedp(goods[number]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[number]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[number]["dbase"][key[j]]);
        item->delete("equipped");
    }

    if( !item->move(who) ) {
        tell_object(who, NAME+"發現你似乎拿不動這樣商品，便不還你了。\n");
        // 刪除物品
        destruct(item);
        return 0;
    }

        tell_object(who, "你從" + NAME + "取回了" + item->query("name") + "。\n");

    //從列表中刪除
    map_delete(goods, number);

    save();
    return 1;
}

/*

// 在remove()時才進行save()動作
int remove()
{
    save();
    return 1;
}
*/
