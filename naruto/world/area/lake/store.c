#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "倉庫");
    set("long", @long
裡面散發出股潮溼的霉味，看著門牌上寫著「倉庫」的字樣，
應該能夠想象當這裡沉入水中時，裡面也堆了不少東西吧，只是經
過了不知道多少年的浸泡，大概全都已經腐爛不能用了。
long);
    set("exits", ([
        "north" : ([ "filename": __DIR__"relice.c",
                      "x_axis": 7,
                      "y_axis": 7,
                 ]),
        "east" : __DIR__"store2.c",
    ]));
    setup();
}
