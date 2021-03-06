#include <login.h>
#include <ansi.h>

inherit ITEM;

mapping record = ([
    1: ([ "name": HIR"火之國"NOR+BGRN"木葉村"NOR,
          "file": _DIR_AREA_"muye/inn.c", ]),

    2: ([ "name": "   "BBLU+HIW"鯨魚島"NOR"   ", 
          "file": _DIR_AREA_"whale_island/mite_hotel.c", ]),

    3: ([ "name": "袁大師工作室",
          "file": "/u/a/alickyuen/workarea.c",
          "x": 8,
          "y": 6, ]),
]);

void create()
{
    set_name(HIC"傲天"HIW"追仙劍"NOR, ({ "Ao Tian Sword", "sword"}));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "柄");
        set("value", -1);
        set("no_get", 1);
        set("long", "一柄插帶著劍鞘插在庭中的神劍，劍身散發出凜冽的寒氣，讓人不寒\n"
                    "而慄。有什麼方法能將這把劍拔出呢？");
    }
    setup();
}
void init()
{
    add_action("do_fsword", "fsword");
    add_action("do_list", "list");
}
int do_fsword(string arg)
{
    int x, y, number;
    string file, out_msga, out_msgb, in_msg;
    object me = this_player(), room;

    out_msga = HIY"$N"HIY"兩手合十，口中喃喃默唸，忽然"NOR"$n"HIY"「堅」地一聲從劍鞘中飛出！\n"NOR;
    out_msgb = HIY"只見$N"HIY"一個翻身躍上"NOR"$n"HIY"，口唸劍訣快速地飛離了此地。\n\n"NOR;
    in_msg = "四週忽然傳出一聲劍嘯，只見$N御著長劍劃破天空降落在這裡。\n"NOR;

    // 只有巫師可以御劍
    if( !wizardp(me) ) {
        message_vision("$N照著石壁上的咒文唸了一遍，卻沒發生任何事情。\n", me);
        return 1;
    }

    // 忙碌或戰鬥中不可御劍
    if( me->is_busy() || me->is_fighting() ) 
        return notify_fail("你現在沒有空。\n");

    // 沒指定目標物
    if( !arg )
        return notify_fail("你想要傳送到哪裡？\n");

    // 當目標物為設定內所有的編號房間
    if( sscanf(arg, "%d", number) == 1 ) {
        if( undefinedp(record[number]) )
            return notify_fail("你想要傳送到哪裡？\n");

        if( !objectp(room = load_object(record[number]["file"])) )
            return notify_fail("你現在無法傳送到那個地方。\n");

        // 當編號有設定座標時則飛往座標位置
        if( record[number]["x"] != 0 && record[number]["y"] != 0 ) {
            message_vision(out_msga, me, this_object());
            message_vision(out_msgb, me, this_object());
            area_move(room, me, record[number]["x"], record[number]["y"]);
            message_vision(in_msg, me);
            return 1;
        }
        message_vision(out_msga, me, this_object());
        message_vision(out_msgb, me, this_object());
        me->move(room);
        message_vision(in_msg, me);
        return 1;
    }

    // 飛往系統路境的檔案
    if( sscanf(arg, "%s %d %d", file, x, y) == 3 ) {
        file = resolve_path(me->query("cwd"), file);
        if( !sscanf(file, "%*s.c") ) file += ".c";
        if( file_size(file) >=0 && (room=load_object(file)) ) {
            if( !room->is_area() ) return 1;
            message_vision(out_msga, me, this_object());
            message_vision(out_msgb, me, this_object());
            area_move(room, me, x, y);
            message_vision(in_msg, me);
            return 1;
        } else {
            write("這個區域檔不存在。\n");
            return 1;
        }
    }
    room = find_player(arg);
    if( !room ) room = find_living(arg);
    if( room == me ) {
        write("你要移到自已身旁？\n");
        return 1;
    }
    if( !room || !room->visible(me)) {
        arg = resolve_path(me->query("cwd"), arg);
        if( !sscanf(arg, "%*s.c") ) arg += ".c";
        if( file_size(arg) >=0 && (room=load_object(arg)) ) {
            if( room->is_area() ) {
                write("移動到區域物件，必需加上座標才能移動。\n");
                return 1;
            }
            message_vision(out_msga, me, this_object());
            message_vision(out_msgb, me, this_object());
            me->move(room);
            message_vision(in_msg, me);
            return 1;
        } else return notify_fail("這個地方不存在。\n");
    }

    // 飛向人物(id不可為復數)
    if( environment(room)->is_area() ) {
        if( area_environment(room, me) ) return notify_fail("你已經在他身旁了。\n");
            message_vision(out_msga, me, this_object());
            message_vision(out_msgb, me, this_object());
        if( !area_move(environment(room), me, room->query("area_info/x_axis"), room->query("area_info/y_axis")) ) {
            tell_object(me, "因為某種理由，你的 goto 失敗了。\n");
        }
    } else {
        message_vision(out_msga, me, this_object());
        message_vision(out_msgb, me, this_object());
        if( !me->move(environment(room)) ) {
            tell_object(me, "因為某種理由，你的 goto 失敗了。\n");
        }
    }
    message_vision(in_msg, me);
    return 1;
}
int do_list()
{
    string msg;
    int index, size, x, y;

    msg  = "╭────────────────────────╮\n";
    msg += "│                                                │\n";
    msg += "│  "HIC"孤山獨人    孤思群城    御劍萬里    足踏中原"NOR"  │\n";
    msg += "│                                                │\n";
    msg += "│  "HIY"心誠則置    心想事成    神劍破空    嘯天而行"NOR"  │\n";
    msg += "│                                                │\n";
    msg += "├────────────────────────┤\n";
    msg += "│編號      地區          (X,Y)起點位置           │\n";
    msg += "├────────────────────────╯\n";

    if( (size=sizeof(record)) )
        for(index=1;index<=size;index++)
            if( record[index]["x"]==0 && record[index]["y"]==0 ) {
                msg += sprintf("│%4d  %9s         房間無座標\n", index, record[index]["name"]);
            } else {
                msg += sprintf("│%4d  %9s         (%d,%d)\n", index, record[index]["name"], record[index]["x"], record[index]["y"]);
            }

    msg += "├────────────────────────╮\n";
    msg += "│fsword <人物>|<房間>|<區域> <X座標> <Y座標>     │\n";
    msg += "╰────────────────────────╯\n\n";

    write(msg);
    return 1;
}
