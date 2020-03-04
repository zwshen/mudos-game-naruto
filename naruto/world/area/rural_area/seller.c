#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "商人邸");
    set("long", @LONG
佈置很簡單的商人家，不像一般大商人都會故意把家裡佈置的非
常豪華。只見一位頂著啤酒肚的商人笑咪咪的靠近你，向你推銷農村
這季收成的各種作物。「不喜歡生食也沒關係∼柴米油鹽醬醋茶∼我
們這裡應有盡有喔！」商人濤濤不絕的推薦著。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"area.c",
                       "x_axis" : 31,
                       "y_axis" : 7,
                  ]),
    ]));
    set("objects", ([
        __DIR__"npc/seller.c" : 1,
    ]));
    setup();
}
