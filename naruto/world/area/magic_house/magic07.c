#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "¹Îªø«Ç");
    set("long", @LONG
¦ì©ó¤»¨~¬P¥k°¼ªº¹Îªø«Ç¤¤¡A¹Îªø¨¥®p†ýŠàº¡Áy¯º®eªº¦V§A°Ý¦n
¡A¦ý¬O§A«oÁô¬ùªº·PÄ±¨ì³o©Ð¶¡¤¤¦³ºØ»¡¤£¥XªºÃø¹L·P¡A§AÀH«K¥´°¨
ªê¸ò¹Îªø«¢°Õ¤F´X¥y¡A«K§Ö¨BÂ÷¶}«Î¤l¡A¦bÁ{¨««e¦ü¥GÅ¥¨ì¨¥®p†ýŠà
¦b©Ð¶¡¤¤¸ò¬Y¤H¥æ½ÍµÛ....¦ý¬O§A­è¤~¶i¥h¨Ã¨S¬Ý¨ì¤Hªü¡H
LONG);
    set("exits", ([
        "west" : __DIR__"magic06.c",
        "east" : __DIR__"magic08.c",
        "north" : __DIR__"magic03.c",
        "south" : __DIR__"magic11.c",
    ]));
    set("objects", ([
        __DIR__"npc/yan.c" : 1,
    ]));
    setup();
    set("no_recall", 1);
}
void init()
{
    add_action("do_move", "move");
    add_action("do_move", "sfly");
}
int do_move(string arg)
{
    message_vision("$N¥ø¹Ï­¸¤W¤ÑªÅ¡A¦ý¬O¼²¨ì©Ð³»¤S¶^¤F¤U¨Ó¡C\n", this_player());
    return 1;
}
