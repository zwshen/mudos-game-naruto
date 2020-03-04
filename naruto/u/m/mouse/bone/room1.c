#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "獸欄");
        set("long", @LONG
一塊用欄杆圍起來的空間，但是裡面除了一些魚肉之外沒有其他
的東西，那些魚肉似乎才剛放出來，看起來還非常的新鮮。偶然間發
現到有些斷裂的欄杆，居然有類似熊的毛髮類物品留在上面，難道蛇
族還養熊當寵物？真是奇怪的族群。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"marsh.c",
                       "x_axis" : 24,
                       "y_axis" : 8,
                  ]),
    ]));
    setup();
}
