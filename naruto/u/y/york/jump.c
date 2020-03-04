inherit ROOM;

void create()
{
   set("short","旅行之泉");
   set("long", @LONG
看過勇者鬥惡龍都知道這幹麻的吧。
LONG);
   set("exits", ([
      "wizard": "/world/area/wizard/guildhall",
      "wild": (["filename": "/world/area/wild/wild.c",
                              "x_axis": 7,
                              "y_axis": 17
                ]),
      "forest": (["filename": "/world/area/wild/forest.c",
                              "x_axis": 15,
                              "y_axis": 1
                ]),
      "land": (["filename": "/world/area/wild/land.c",
                              "x_axis": 25,
                              "y_axis": 4
                ]),
      "mystic_forest": (["filename": "/world/area/wild/mystic_forest.c",
                              "x_axis": 22,
                              "y_axis": 3
                ]),
      "muye": "/world/area/muye/inn",
      "sewer": (["filename": "/world/area/muye/sewer.c",
                              "x_axis": 26,
                              "y_axis": 28
                ]),
      "swanlake": (["filename": "/world/area/muye/swanlake.c",
                                 "x_axis": 33,
                                 "y_axis": 19
                   ]),
      "deadforest": (["filename": "world/area/muye/deadforest.c",
                                  "x_axis": 16,
                                  "y_axis": 1
                    ]),
    ]));
   set("objects",([
      __DIR__"item/stone.c": 1
   ]));

    setup();
}

