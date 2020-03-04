inherit ROOM;

void create()
{
        set("short", "小木屋");
        set("long", @LONG
一間普通的小木屋和一個閒到打假人耗時間的巫師。
LONG);
    set("exits", ([
        "jump": __DIR__"jump.c",
        "acme": "/u/a/acme/workroom.c",
        "up"   : ([ "filename" : "/u/y/york/area/york.c",
                                 "x_axis" : 0,
                                 "y_axis" : 5
                 ])
    ]));
   set("objects",([
       _DIR_NPC_"stake.c":1
   ]));

        setup();
    load_object("/daemon/board/york");
}

