#include <ansi.h>
inherit ROOM;

mapping record = ([
    1: ([ "name": BGRN"古老森林"NOR,
          "file": _DIR_AREA_"old_forest/monkey.c",
          "x": 1,
          "y": 10,
       ]),
    2: ([ "name": BBLU+HIW"天鵝湖底"NOR,
          "file": _DIR_AREA_"lake/lake.c",
          "x": 13,
          "y": 18,
       ]),
    3: ([ "name": BGRN+HIG"刺松林"NOR,
          "file": _DIR_AREA_"thorn_pine/pine.c",
          "x": 15,
          "y": 1,
       ]),
    4: ([ "name": HIK"陰影小徑"NOR,
          "file": _DIR_AREA_"sneakhole/path.c",
          "x": 8,
          "y": 38,
       ]),
    5: ([ "name": HIM"回音山洞"NOR,
          "file": _DIR_AREA_"echo/echo.c",
          "x": 15,
          "y": 19,
       ]),
    6: ([ "name": BRED+HIW"骸骨"BRED+HIR"戰場"NOR,
          "file": _DIR_AREA_"bone/bone.c",
          "x": 6,
          "y": 39,
       ]),
    7: ([ "name": BRED+HIW"司法島"NOR,
          "file": _DIR_AREA_"sifa_isle/sifa.c",
          "x": 45,
          "y": 38,
       ]),
    8: ([ "name": HIY"梅莉號"NOR,
          "file": _DIR_AREA_"ship/lufi.c",
          "x": 29,
          "y": 29,
       ]),
    9: ([ "name": BGRN+HIY"小荒島"NOR,
          "file": _DIR_AREA_"barren_isle/barren.c",
          "x": 24,
          "y": 3,
       ]),
   10: ([ "name": BMAG+HIW"魔術馬戲團"NOR,
          "file": _DIR_AREA_"magic_house/house.c",
          "x": 15,
          "y": 19,
       ]),
   11: ([ "name": YEL"地下沙穴"NOR,
          "file": _DIR_AREA_"sand_hole/sand.c",
          "x": 15,
          "y": 15,
       ]),
   12: ([ "name": HIY"鄉野"HIG"農村"NOR,
          "file": _DIR_AREA_"rural_area/area.c",
          "x": 18,
          "y": 18,
       ]),
   13: ([ "name": YEL"神獸"GRN"森林"NOR,
          "file": _DIR_AREA_"god_forest/god_1.c",
          "x": 22,
          "y": 12,
       ]),
   14: ([ "name": BRED+HIW"火山"NOR"列島",
          "file": _DIR_AREA_"lv60_area/fire_isle.c",
          "x": 10,
          "y": 6,
       ]),
]);

string do_list()
{
    int index, size;
    string msg;

    if( !wizardp(this_player()) ) {
        msg  = "\n\n一堆亂七八糟的鬼畫符，根本看不懂。\n";
        return msg;
    }
    msg  = "╭────────────────────────╮\n";
    msg += "│五芒星傳送陣                                    │\n";
    msg += "├────────────────────────┤\n";
    msg += "│編號   地區            (X,Y)起點位置            │\n";
    msg += "├────────────────────────╯\n";

    if( (size=sizeof(record)) )
        for(index=1;index<=size;index++)
        msg += sprintf("│%4d  %12s     (%d,%d)\n", index, record[index]["name"], record[index]["x"], record[index]["y"]);

    msg += "├────────────────────────╮\n";
    msg += "│輸入 ffly <編號> <X座標> <Y座標>  進行傳送。    │\n";
    msg += "╰────────────────────────╯";

    return msg;
}
void create()
{
    set("short", HIW"草"HIG"摩"NOR"家");
    set("long", @LONG
在僕人的用心整理下，草摩家終於改變了原有的風貌，成為一個
乾淨的家。為了主人使用的方便，她還在房間內放置了一座工作計劃
板，讓主人不要忘東忘西的，該記錄的東西就寫在板上。稍微看過房
間擺設後，你發現房間右上角有個五芒星，不知是做什麼的。左邊角
落則有一扇木門，隱約可以聞到一樂拉麵店的拉麵香。
LONG);
    set("exits", ([
        "down" : ([ "filename": _DIR_AREA_"wizard/wizard.c",
                      "x_axis": 14,
                      "y_axis": 5,
                 ]),
        "east" : __DIR__"bathing.c",
        "north" : __DIR__"tomb.c",
        "test" : __DIR__"workroom2.c",
    ]));
    set("detail", ([
        "木門": "似乎可以打開(open)出去的樣子。",
        "五芒星": (: do_list :),
    ]));
    set("objects", ([
        __DIR__"npc/vaga.c" : 1,
    ]));
    setup();
    load_object("/u/m/mouse/board.c");
}
void init()
{
    if( wizardp(this_player()) ) {
        add_action("do_ffly", "ffly");
        add_action("do_gojail", "gojail");
    }
    add_action("do_open", "open");
}
int do_open(string arg)
{
    if( arg == "木門" || arg == "門" ) {
        message_vision("$N將木門打開，緩緩的走了出去。\n", this_player());
        this_player()->move(_DIR_AREA_"muye/inn");
        message_vision("$N從拉麵店旁邊的木門走了出來。\n", this_player());
        this_player()->start_busy(1);
        return 1;
    }
    return notify_fail("你想打開什麼？\n");
}
int do_gojail(string arg)
{
    message_vision("$N"HIR"打開暗門走了進去。\n"NOR, this_player());
    this_player()->move(_DIR_AREA_"jail.c");
    message_vision("$N"HIR"忽然出現在這觀察有沒有人被關。\n"NOR, this_player());
    return 1;
}
int do_ffly(string arg)
{
    int number, x, y;
    object me = this_player(), room;

    if( me->is_busy() || me->is_fighting() ) 
        return notify_fail("你現在沒有空。\n");

    if( !arg )
        return notify_fail("你想要飛到哪個區域？\n");

    if( sscanf(arg, "%d %d %d", number, x, y) != 3 )
        return notify_fail("你想要飛到區域中需要加上座標。\n");

    if( undefinedp(record[number]) )
        return notify_fail("你想要飛到哪個區域？\n");

    if( x < 0 || y < 0 )
        return notify_fail("沒有這個座標可以飛。\n");

    if( !objectp(room = load_object(record[number]["file"])) )
        return notify_fail("你這個地方目前無法傳送\n");

    message_vision("$N忽然飛了起來，慢慢消失在這裡。\n", me);

    if( !area_move(room, me, x, y) ) {
        message_vision("結果$N突然失去重心，又從空中跌了下來。\n", me);
        return 1;
    }
    message_vision("$N從天而降，安穩的降落在這裡。\n", me);
    return 1;
}
int valid_leave(object me, string dir)
{
    int x, y;
    if( !me ) return 0;
    if( !userp(me) && dir == "down" ) return 0;
    if( userp(me) && dir == "test" ) {
        if( !wizardp(me) ) return notify_fail("這裡只有巫師才能進去。\n");
    }
    return ::valid_leave(me, dir);
}
