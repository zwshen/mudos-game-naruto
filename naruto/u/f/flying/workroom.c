#include <room.h>

// 設成INN者，會自動成為非戰區，並且是重生點
inherit INN;

void create()
{
    set("short", "魅影之間");

    set("long", @long
這裡是魅影之間，奇特的紫色霧氣瀰漫著整個空間，有幾個顏色較深色
的紫色氣團樣子很像桌椅，坐上去之後也異常柔軟。紫氣帶有點紫羅蘭
的氣味，讓人不知不覺的放鬆了不少
long);

    set("exits", ([
        "acme" : "/u/a/acme/workroom.c",
        "kkeenn" : "/u/k/kkeenn/workroom.c",
        "ayumi" : "/u/a/ayumi/workroom.c", 
        "east" : ([ "filename" : "/u/f/flying/area/mei.c",
                                         "x_axis" : 8,
                                          "y_axis" : 9,  
                                  ]),
        "down" : ([ "filename" : "/u/f/flying/area/rod.c",
                                         "x_axis" : 5,
                                         "y_axis" : 5,
                                  ]),
    ]));



    setup();
    replace_program(ROOM);
}


