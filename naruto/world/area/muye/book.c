/* write by -Acme- */

inherit ROOM;

void create()
{
    set("short", "木葉書店");

    set("long", @long
這是一間堆滿圖書的小型書店，當你還沒進到書店裡時就被門口
的一副聯子吸引，上面寫著「書到用時方恨少，一洩千里誰知道」看
來這間書店又是盡賣一些不良的書藉，當你在書店左顧右盼時，老闆
不時的傳來咳嗽聲，似乎對你的白看書感到相當不滿。
long);

    set("exits", ([
        "west" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 15,
                      "y_axis": 10,
                 ]),
    ]));

    set("objects", ([
        __DIR__"npc/booker.c": 1,
    ]));

    setup();
}
