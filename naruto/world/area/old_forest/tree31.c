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
        "north" : __DIR__"tree25.c",
        "west" : __DIR__"tree30.c",
        "east" : __DIR__"tree32.c",
    ]));
    set("objects", ([
        __DIR__"npc/shooter.c" : 1,
        __DIR__"npc/warrior.c" : 1,
    ]));
    setup();
}
