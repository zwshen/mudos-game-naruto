#include <ansi.h>
inherit ROOM;

void create()
{
    set("short","�j�ˤW�K");

    set("long", @long
�|�P��ۤp�p���O�l�A�J�Ӥ@�ݥi�H�o�{�q�o�̩~�M����@�s��
�~�@�����W�Ӫ���K�I�u���|�P���M�_�X�F���֤g�ۡA�L�̤⮳�}�b
�A�j���O�b�o�̰�ŧ�J�I�̡C
long);
    set("exits", ([
        "west" : __DIR__"tree22.c",
        "east" : __DIR__"tree24.c",
        "south" : __DIR__"tree28.c",
    ]));
    set("objects", ([
        __DIR__"npc/shooter.c" : 2,
    ]));
    setup();
}