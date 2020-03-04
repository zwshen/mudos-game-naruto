#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "¤p«Î");
    set("long", @LONG
³o¸Ì¥u¦³Â²­®¦aÂ\©ñ¤F´X±i¤ì´È©M¤@­Ó¤ì®à¡A¾aÀðªº¨º¤@ºÝ¦³¤@
±i¯}ÂÂªº¤ì§É¡A¬O¤@¶¡«Ü´¶³qªº¤p«Î¡C¦ÓÀð¤W±¾µÛ´X°¦ÅK»s«o¥Íù×ªº
¾¹¨ã¡C¤@®ÇÃÃ»sªºÂd¤l³Q¥´¤F¶}¨Ó¡A­·¤@§j«Kµo¥X¡u U U¡ã§r§r¡ã¡v
ªºÁn­µ¡C
LONG);

    set("exits", ([
        "west" : ([ "filename" : __DIR__"land.c",
                    "x_axis" : 25,
                    "y_axis" : 4,
                 ]),           
        "east" : __DIR__"house2.c",
    ]));

    set("objects", ([
        __DIR__"npc/qinqin.c" : 1,
    ]));

    setup();
}
