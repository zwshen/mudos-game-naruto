/* hockshop.c
   write by -Acme-
*/

// #pragma save_binary

#define GOODS_MAXIMUM 100

#include <dbase.h>
#include <ansi.h>
#include <room.h>

inherit F_SAVE;
inherit ROOM;

mapping goods;

mapping query_goods() { return goods; }

int to_stock(object item)
{
    int index, amount, changed;
    string file;

    // goods 不是一個物件
    if( !objectp(item) ) return 0;

    if( base_name(item)[0..6] != "/world/" ) return 0;

    // 商品列表已滿
    if( sizeof(goods) >= GOODS_MAXIMUM ) {
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
            map_delete(goods, index);
        }
    }

    amount = item->query_amount();
    if( !amount ) amount = 1;

    file = base_name(item);

    changed = item->query("changed");

    // 若貨品是沒有經過「改變」也就是貨品的設定與原始檔案設定相同，則
    // 檢查是否與商品列表中的某商品相同，如果相同，即增加數量便可。
    if( !changed ) {
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;

            // 找到相同的檔案名稱，增加其數量
            if( goods[index]["file"] == file ) {
                goods[index]["amount"] += amount;
                destruct(item);
                return 1;
            }
        }
    }

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

    if( item->query("base_value") ) goods[index]["value"] = item->query("base_value");
    else goods[index]["value"] = item->query("value");

    if( item->query("wear_as") ) goods[index]["class"] = BBLU"防具"NOR;
    else if( item->query("wield_as") ) goods[index]["class"] = BRED"武器"NOR;
    else if( function_exists("stuff_ob", item) ) goods[index]["class"] = BGRN"食品"NOR;
    else goods[index]["class"] = BYEL"其它"NOR;

    if( item->query("base_unit") ) goods[index]["unit"] = item->query("base_unit");
    else if( item->query("unit") ) goods[index]["unit"] = item->query("unit");
    else goods[index]["unit"] = "個";


    // 經過修改過的物品，儲存完整的物品資料
    if( changed ) {
        mapping dbase = item->query_entire_dbase();
        if( mapp(dbase) )
            goods[index]["dbase"] = dbase;
    }

    destruct(item);

    return 1;
}

int to_sell(object who, int number, int amount)
{
    int value;
    object item;

    if( !objectp(who) ) return 0;

    if( sizeof(all_inventory(who)) >= 40 ) {
        tell_object(who, "店家發現你似乎拿不動這樣商品，便不賣你了。\n");
        return 1;
    }

    if( who->query_encumbrance() >= who->query_ability("carriage") ) {
        tell_object(who, "店家發現你似乎拿不動這樣商品，便不賣你了。\n");
        return 1;
    }

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

    // 數量檢查
    if( !amount ) amount = 1;
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
        tell_object(who, "店家發現這個商品有問題後隨即下架了，你無法購買。\n");
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
        tell_object(who, "店家發現你似乎拿不動這樣商品，便不賣你了。\n");
        // 刪除物品
        destruct(item);
        return 1;
    }

    message_vision("$N花了" + chinese_number(value) + "兩銀子向" + this_object()->query("short") + "買下" +
                   chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "。\n", who);

    // 從銀行扣錢
    who->add("bank", -value);

    // 商品數量改變
    goods[number]["amount"] -= amount;

    // 賣完了，從列表中刪除
    if( goods[number]["amount"] <= 0 ) map_delete(goods, number);

    return 1;
}

string do_identify(object obj)
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


string do_list(string arg)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "目前沒有任何商品。\n";

if( stringp(arg) ) {
object item;
index = atoi(arg);
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

    msg = do_identify(item);
    destruct(item);
    return msg;
}

    msg  = "╭──────────────────────────────────╮\n";
    msg += sprintf("│%-68s│\n", this_object()->query("short") + "目前的商品列表" );
    msg += "├──────────────────────────────────┤\n";
    msg += "│編號  類別    數量  單價/銀兩  名稱                                 │\n";
    msg += "├──────────────────────────────────╯\n";
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        msg += sprintf("│%4d  %s %7d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
    }
    msg += "├──────────────────────────────────╮\n";
    msg += "│輸入 help trade 瞭解如何使用交易指令。                              │\n";
    msg += "╰──────────────────────────────────╯";
    
    return msg;
}

// 儲存當舖資料的路徑位置
string query_save_file() { return file_name(this_object()); }

// 這是當舖
int is_hockshop() { return 1; }

// 在reset()時才進行save()動作
//void reset() { save(); }

// 在remove()時才進行save()動作
void remove()
{
    if (inherits(HOCKSHOP, this_object()))
    {
        save();
    }
}

void setup()
{
    if( !restore() ) goods = ([]);
}
