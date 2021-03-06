#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIC"天然居"NOR);
    set("long", @long
散發著自然氣息的小屋，四周都被大片的森林所包圍，房間中的
擺設也都是由樹木所製成，飄著獨特的木香。只見房間中坐著一位青
年男子，他正盯著桌上的木製棋盤，上面黑子白子鬥爭激烈，你上前
湊進一看，發現這棋局黑白不分，水火不容，好似黑子贏過白子，又
感覺白子的棋路較有空間發展，就在你苦思間突然醒悟，差點連自己
也掉進這棋盤的迷思中了。
long);
    set("exits", ([
        "south" : ([ "filename": __DIR__"god_1.c",
                      "x_axis": 2,
                      "y_axis": 4,
                 ]),
    ]));
    set("objects", ([
        __DIR__"npc/man.c" : 1,
    ]));
    set("no_recall", 1);
    set("no_fight", 1);
    setup();
}
