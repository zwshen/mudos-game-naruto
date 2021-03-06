#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIC"歡樂寶箱"NOR, ({ "happy box", "box" }));

    if( !clonep() ) {
        set("base_unit", "箱");
        set("base_value", 4000);
        set("base_weight", 10);
        set("no_box", 1);
        set("long", "一個神奇的寶箱，你忍不住想打開(use)看裡面有什麼。\n");
    }
    setup();
}

object do_random(string category)
{
    int rnd, *key;
    key = keys(ITEM_D->do_query_all(category));
    rnd = key[random(sizeof(key))];
    return ITEM_D->get_item(category, rnd);
}

int do_use(object me, string arg)
{
    object item, *inv;

    inv = all_inventory(this_player());

    switch( random(10000)+1 ) {
        case 101..300: item = do_random("wp"); break;   // 2%
        case 301..800: item = do_random("eq"); break;   // 5%
        case 801..2800: item = do_random("obj"); break; // 20%
        default: item = do_random("food"); break;       // 73%
    }
    if( !objectp(item) ) {
        tell_object(me, "寶箱又突然合了起來。\n");
        return 1;
    }

    // 判斷身上物品數量，因為不加這行會發生開不到物品
    // 卻可以一直開到歡樂箱增加的bug
    if( sizeof(inv) >= 40 ) {
        tell_object(me, "你身上太多東西，再也拿不動了。\n");
        return 1;
    }

    // 開到無法開到的物品，會補償 1~5 個箱子
    if( item->query("no_box") != 0 ) {
        int i = 1 + random(5);
        message_vision("$N雙手挫了挫，順便沾一下路邊的狗屎，便將$n打了開來。\n", me, this_object());
        message_vision("忽然從$n中又跳出了"HIC"("+i+")"NOR"個$n...$N慌張的全部撿了起來。\n", me, this_object());

        if( this_object()->query("keep_this") == 1 ) {
            this_object()->add_amount(i-1);
            this_object()->set("keep_this", 1);
        } else {
            this_object()->add_amount(i-1);
        }
        return 1;
    }

    // 貴重物品機率沒開到，補償 1 個箱子
    if( item->query("value") >= 150000 || item->query("base_value") >= 50000 ) {
        if( random(1000) > random(10) ) {
            message_vision("$N雙手挫了挫，順便沾一下路邊的狗屎，便將$n打了開來。\n", me, this_object());
            message_vision("$N發現裡頭裝著一個$n...\n", me, this_object());
            return 1;
        }
    }

    if( !item->move(me) ) {
        destruct(item);
        tell_object(me, "你身上太多東西，再也拿不動了。\n");
        return 1;
    }

    message_vision("$N雙手挫了挫，順便沾一下路邊的狗屎，便將$n打了開來。\n", me, this_object());
    message_vision("$N發現裡頭裝著一個$n...\n", me, item);

    // 個數減少
    this_object()->add_amount(-1);
    if( !this_object()->query_amount() )
        destruct(this_object());

    return 1;
}
