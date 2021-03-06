#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "室內出動間");
        set("long", @LONG
一間很特別的房間，牆壁四周的木板都有經過特殊處理，好像沾
著一層薄膜，就算被水潑到也不會濕掉。在房間右邊有一個開關，開
關的旁邊還有一塊木板與四周牆壁是有間格的，也許和開關有什麼用
途吧。左邊則放了一些潛水的用具。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"lufi.c",
                       "x_axis" : 34,
                       "y_axis" : 28,
                  ]),
    ]));
    set("detail", ([
        "開關": "不知道做什麼用的開關，可以打開(open)。",
    ]));
    setup();
}
void init()
{
    add_action("do_open", "open");
}

int do_open(string arg)
{
    object me, area;
    string area_file = "/world/area/benthal/sea2.c";

    me = this_player();

    if( !arg ) return 0;
    if( arg != "開關" ) return 0;

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    message_vision("$N用力拉下開關，大門「碰」地一聲關了起來，一陣大水把$N沖出去了...\n", me);
    if( !area_move(area, me, random(15)+16, random(9)+24) ) return 0;
    message_vision("結果$N被衝到了這個地方。\n", me);
    return 1;
}
