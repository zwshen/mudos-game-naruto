inherit ROOM;

void create()
{
        set("short", "梟屋");
        set("long", @LONG
牆壁上掛滿了素描，所畫的全都是一種時常聽人說言小型翼王類
巨鳥「蒼之梟」不過很少聽人看過蒼之梟的樣子，這次卻能在這裡看
到蒼之梟的各種姿態素描，表示這間房子的主人對於這種翼王類應該
有相當深入的了解。
LONG);
    set("exits", ([
        "west" : ([ "filename" : __DIR__"village.c",
                       "x_axis" : 26,
                       "y_axis" : 28,
                  ]),
    ]));
    set("objects", ([
        __DIR__"npc/shao.c" : 1,
    ]));
    setup();
}
