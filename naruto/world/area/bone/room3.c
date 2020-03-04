#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "兵器");
        set("long", @LONG
房內擺放著一些草人，不過每一個都被打的遍體鱗傷。牆壁上掛
了一些蛇族所穿的盔甲和武器，所見的盔甲都是藤製的盔甲，武器則
以彎刀和長槍為主，表示蛇族在戰鬥時非常注意速度，都選用較輕的
籐做為防具，武器則用攻擊範圍較廣的彎刀長槍。
LONG);
    set("exits", ([
        "north" : ([ "filename" : __DIR__"marsh.c",
                       "x_axis" : 6,
                       "y_axis" : 13,
                  ]),
    ]));
    setup();
}
