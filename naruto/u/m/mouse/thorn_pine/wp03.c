inherit ROOM;

void create()
{
        set("short", "�Z����");
        set("long", @LONG
�@�ؼ��x�����D�A�Z�h�B�Ԥh�����D�A�K�������D�C�q��W����
�h��Ƥ��M���Z���A�N�F�Ѭ�����~�����۵P�����ۡu�Z�����v���W
���C�b�o�̪���W�ٱ��F�t�@���P�l�g�ۡu�t���L�v
LONG);
    set("exits", ([
        "west" : __DIR__"wp01.c",
    ]));
    set("objects", ([
        __DIR__"npc/may.c" : 1,
    ]));
    setup();
}