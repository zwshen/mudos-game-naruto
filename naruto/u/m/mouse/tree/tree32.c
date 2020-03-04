#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","古森上枝");

    set("long", @long
沿路的土著出現愈來愈平凡，看來快到土著所住的村子了吧，也
許還能一探木葉村中所傳說的那棵古老巨木。
long);
    set("exits", ([
        "west" : __DIR__"tree31.c",
        "east" : __DIR__"tree33.c",
    ]));
    set("objects", ([
        __DIR__"npc/shooter.c" : 1,
        __DIR__"npc/warrior.c" : 2,
    ]));
    setup();
}
