/* transfer.c write by -Acme- */
#include <ansi.h>

inherit ROOM;

mapping record = ([
    1: ([ "name": HIR"火之國"NOR+BGRN"木葉村"NOR,
          "file": _DIR_AREA_"muye/inn.c",
         "price": 100 ]),
      2: ([ "name": BBLU+HIW"鯨魚島"NOR,
            "file": _DIR_AREA_"whale_island/mite_hotel.c",
           "price": 100 ]),
    3: ([ "name": BRED+HIW"司法島"NOR,
          "file": _DIR_AREA_"sifa_isle/sea.c",
         "price": 100 ]),


/*
    2: ([ "name": "水之國霧忍村",
          "file": _DIR_AREA_"muye/inn.c",
         "price": 100 ]),
*/
]);

string do_list()
{
    int index, size;
    string msg;

    msg  = "╭────────────────────────╮\n";
    msg += "│五行傳送特別服務                                │\n";
    msg += "├────────────────────────┤\n";
    msg += "│編號  單價/銀兩  地區                           │\n";
    msg += "├────────────────────────╯\n";

    if( (size=sizeof(record)) )
        for(index=1;index<=size;index++)
            msg += sprintf("│%4d  %9d  %s\n", index, record[index]["price"], record[index]["name"]);

    msg += "├────────────────────────╮\n";
    msg += "│輸入 transfer <編號> 進行傳送。等級一免費！     │\n";
    msg += "╰────────────────────────╯";

    return msg;
}

void create()
{
    set("short", "五行傳送");
    set("long", "這裡充斥著一股強烈的查克拉，可能是某位忍者在此佈下特別的\n"
                "忍術，你可以發現四週掛滿了忍術卷軸，而在你的正前方立著一張大\n"
                "牌子，上頭亂七八糟地寫了一堆文字。\n" );

    set("detail", ([
        "牌子" : (: do_list :),
    ]));

    set("exits", ([
        "east" : ([ "filename" : __DIR__"wizard.c",
                       "x_axis" : 21,
                       "y_axis" : 20,
                  ]),
        "south" : ([ "filename" : __DIR__"wizard.c",
                       "x_axis" : 18,
                       "y_axis" : 23,
                  ]),
        "west" : ([ "filename" : __DIR__"wizard.c",
                       "x_axis" : 15,
                       "y_axis" : 20,
                  ]),
        "north" : ([ "filename" : __DIR__"wizard.c",
                       "x_axis" : 18,
                       "y_axis" : 17,
                  ]),
    ]));

    setup();
}

void init()
{
    add_action("do_transfer", "transfer");
}

int do_transfer(string arg)
{
    int number;
    object me = this_player(), room;

    if( me->is_busy() || me->is_fighting() ) 
        return notify_fail("你現在沒有空。\n");

    if( !arg )
        return notify_fail("你想要傳送到哪裡？\n");

    if( sscanf(arg, "%d", number) != 1 )
        return notify_fail("你想要傳送到哪裡？\n");

    if( undefinedp(record[number]) )
        return notify_fail("你想要傳送到哪裡？\n");

    if( me->query("level") != 1 && me->query("bank") < record[number]["price"] )
        return notify_fail("你銀行裡的錢不足，無法傳送。\n");

    if( !objectp(room = load_object(record[number]["file"])) )
        return notify_fail("你現在無法傳送到那個地方。\n");

    message_vision("四週突然颳起了一陣強風，$N一瞬間就被吹走了...\n", me);

    // 移動成功才需付錢
    if( me->move(room) && me->query("level") != 1 ) me->add("bank", -record[number]["price"]);

    message_vision("四週突然颳起了一陣強風，$N被強風帶過來這裡...\n", me);

    me->start_busy(3);

    return 1;
}
