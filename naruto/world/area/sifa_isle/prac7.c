#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "���L�V�m��(��)");
    set("long", @LONG
�o���\��F�X�Ӱ��H�A�i�H�b�o�̽m�ޮ氫�ޯ�C
LONG);

    set("exits", ([
        "east" : __DIR__"prac8",
        "north" : __DIR__"prac4",
    ]));

    set("objects", ([
        _DIR_NPC_"stake.c": 4,
    ]));
    setup();
}