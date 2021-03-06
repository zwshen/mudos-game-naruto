#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

// 一般的魚
string *fish_list = ({
    "/world/item/fish1.c", "/world/item/fish2.c", "/world/item/fish3.c",
    "/world/item/fish4.c", "/world/item/fish5.c", "/world/item/fish6.c",
});

// 特殊物品
string *spec_list = ({
    "/world/area/wild/npc/eq/wolf_head.c",     // 狼頭
    "/world/area/wild/npc/eq/pig_head.c",      // 豬頭
    "/world/area/muye/npc/eq/mouse_head.c",    // 鼠頭
    "/world/eq/head/boiler.c",                 // 鍋子
    "/world/eq/face/fglasses.c",               // 蛙鏡
    "/world/eq/belt/hoop.c",                   // 呼拉圈
    "/world/wp/radish.c",                      // 蘿蔔
    "/world/wp/rattan.c",                      // 藤條
    "/world/wp/sword.c",                       // 短劍
    "/world/wp/dagger.c",                      // 苦無
    "/world/wp/butcher-blade.c",               // 殺豬刀
    "/world/area/muye/npc/eq/go_mouth.c",      // 鳥嘴
});


void create()
{
    set_name("釣竿", ({ "fishing rod", "rod" }));
    set_weight(15000);
    setup_weapon(4, 8, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "righthand" }) );
        set("unit", "根");
        set("value", 1000);
        set("long", "一根普通的釣竿，可以當武器使用，也可以拿來釣魚(fishing)，。\n"
                    "當你釣累了可以放棄(giveup)釣魚。\n" );
    }

    setup();
}
void init()
{
    if( environment(this_object()) && userp(environment(this_object())) ) {
        add_action("do_fishing", "fishing");
        add_action("do_giveup", "giveup");
    }
}

int do_giveup(string arg)
{
if( !this_player()->query_temp("is_fishing") )
return notify_fail("你沒有在釣魚。\n");
    tell_object(this_player(), "你放棄繼續釣魚。\n");
    this_player()->delete_temp("is_fishing");
    return 1;
}

int do_fishing(string arg)
{
int delay;
    object env, me = this_player();

    if( !objectp(env = environment(me)) ) return 0;

    if( !this_object()->query("equipped") ) 
        return notify_fail("必須裝備(wield)釣竿後才可以釣魚。\n");

    if( me->query_temp("weapon/righthand") != this_object() ) 
        return notify_fail("必須裝備(wield)釣竿後才可以釣魚。\n");
    if( me->query_temp("is_fishing") ) return notify_fail("你已經在釣魚了。\n");
    if( me->is_fighting() || me->is_busy() ) return notify_fail("你正在忙，沒辦法釣魚。\n");

    if( env->is_area() ) {
        int x, y;
        x = me->query("area_info/x_axis");
        y = me->query("area_info/y_axis");
        if( !env->query_data(x, y, "fishing") ) return notify_fail("這裡不能釣魚！\n");
    } else {
        if( !env->query("fishing") ) return notify_fail("這裡不能釣魚！\n");
    }
    switch( random(3) ) {
        case 0:
            message_vision("$N用力把釣線甩到湖中央，一屁股坐在岸邊，開始等著魚上鉤...\n",me);
            break;
        case 1:
            message_vision("$N隨手從地上找了幾條蚯蚓當成魚餌，一甩釣線到湖中去，開始釣起魚來...\n",me);
            break;
        default:
            message_vision("$N把釣線理了理，綁上了幾塊饅頭屑，隨即甩了出去，開始釣起魚來...\n",me);
            break;
    }

    me->set_temp("is_fishing", 1);

delay = 5 + random(5);

me->start_busy(delay);

    // 進入釣魚 function
    call_out("fishing_2", delay, me);

    return 1;
}

int fishing_2(object me)
{
    int x=0, y=0, delay;
    object item, env;

    if( !me ) return 1;

    if( !me->query_temp("is_fishing") ) return do_giveup("");
    if( !this_object()->query("equipped") ) return do_giveup("");
    if( me->query_temp("weapon/righthand") != this_object() ) do_giveup("");
    if( !objectp(env = environment(me)) ) return do_giveup("");
    if( me->is_fighting() ) return do_giveup("");

    if( env->is_area() ) {
        x = me->query("area_info/x_axis");
        y = me->query("area_info/y_axis");
        if( !env->query_data(x, y, "fishing") ) return do_giveup("");
    } else {
        if( !env->query("fishing") ) return do_giveup("");
    }

    switch( random(me->query_temp("is_fishing")) ) {
        case 0: message_vision("$N猛著一個「鳳點頭」，原來是釣魚釣到打嗑睡了....\n",me);  break;
        case 1: message_vision("$N站起身來動了幾下手腳，又坐在岸邊，開始釣起魚來....\n",me); break;
        case 2: message_vision("$N發出一陣鬼吼鬼叫，看來是等魚上鉤等著不耐煩了....\n",me); break;
        case 3: message_vision("$N一扯手上的釣竿，才發現魚餌已經被吃光光了...\n",me); break;
        case 4: message_vision("$N收回了釣線，結果一條魚都沒有釣到...\n",me); break;
        case 5: message_vision("$N急急忙忙的收回釣線，結果魚兒一陣掙扎，逃脫去了...\n",me); break;
        default:
            if( random(100) > 1 ) {     // 釣中一般魚
                item = new( fish_list[random(sizeof(fish_list))] );
                if( !objectp(item) ) {
                    message_vision("$N發現這兒的魚已經被釣光了，便收起了釣竿。\n",me);
                    me->delete_temp("is_fishing");
                    return 1;
                }
                message_vision("$N手中的釣線一緊，原來是魚兒上釣了！！\n",me);
                message_vision("$N好整以暇慢慢著收回釣線，發現釣上一"
                                + ( item->query("base_unit") ? item->query("base_unit") : item->query("unit") ) + 
                               "$n了...\n", me, item);
            } else {                    // 釣中特殊物
                item = new( spec_list[random(sizeof(spec_list))] );
                if( !objectp(item) ) {
                    message_vision("$N發現這兒的魚已經被釣光了，便收起了釣竿。\n",me);
                    me->delete_temp("is_fishing");
                    return 1;
                }
                message_vision("$N手中的釣線一緊，原來是魚兒上釣了！！\n", me);
                message_vision("$N好整以暇慢慢著收回釣線，發現釣到個奇怪的物品...\n", me);
            }

            if( !item->move(me) ) {
                message_vision("$N發覺身上滿滿是東西，便把$n丟回水中了...\n", me, item);
                destruct(item);
            }

            me->set_temp("is_fishing", -1-random(3));
            if( me->query_temp("is_fishing") <= 0 )
                me->set_temp("is_fishing", 1);
            break;
    }

    me->add_temp("is_fishing", 1);

    delay = 5 + random(10);
me->start_busy(delay);

    // 進入釣魚 function
    call_out("fishing_2", delay, me);

    return 1;
}
