inherit ROOM;

void create()
{
    set("short", "跌打損傷");
    set("long",@LONG
濃濃的藥味瀰漫在四周，小房間後面是片寬敞的空間，不少的豹
人與受傷的人們正在裡面接受治療。
LONG);
    set("exits", ([
        "south" : ([ "filename" : __DIR__"village.c",
                       "x_axis" : 26,
                       "y_axis" : 6,
                  ]),
    ]));
    
    set("objects", ([
        __DIR__"npc/bi.c" : 1,
    ]));
    setup();
}
