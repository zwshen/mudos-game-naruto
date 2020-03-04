inherit ROOM;

void create()
{
        set("short", "一樓大廳");
        set("long", @LONG
由動物毛皮地毯所鋪成的一塊空地，四周都擺放著桌椅，似乎是
開會時發言者必須站到這裡發言，讓大家都能夠了解發言者的一舉一
動，同時這裡也對著門口，連外面的旁觀者也能窺得一二。
LONG);
    set("exits", ([
        "west" : __DIR__"elder04.c",
        "east" : __DIR__"elder06.c",
        "north" : __DIR__"elder01.c",
        "south" : __DIR__"elder08.c",
    ]));
        setup();
}
