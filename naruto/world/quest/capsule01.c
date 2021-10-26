#include <ansi.h>

void create() { seteuid(getuid()); }

// �������ɬO���ȡA�o�Ө禡���ݭn�ܰ�
int isQuest() { return 1; }

/* �����ȬO�_�୫�Ƹ�  return 0  ���୫��
                       return 1  �i����
   ��ĳ�̦n�]�w���୫�ơC
 */
int isNewly() { return 1; }

// ���ȦW��
string getName() {
    return "���n��������";
}

// ���ȴy�z
string getDetail() {
    string msg;

    msg  = "���F��o�Ĥs�m�һs�@�����_���n�A�A���������L������A�N�O���L\n";
    msg += "�����L�ڴK�H�D���@�Ǧ��ë~�C�Ĥs�m���F�O��s�Įv�A�P�ɤ]�O��\n";
    msg += "���ê̡A���M�L�������F�賣�Z�_�Ǫ�...\n";

    return msg;
}

// ���ȵ���
int getLevel() {
    return 20;
}

/* �������Ȫ��e�m����A�i��O
        1. ���ŻݨD
        2. ¾�~�ݨD
        3. �رڻݨD
        4. �w�����Y�ǥ��ȻݨD
    �����A���i�H�ۥѵo���~�O�C
    �^�ǫD�s�Ȫ�ܲŦX����C
 */
int preCondition(object player) {
    if( player->query("level") > 29 ) return 0;
    if( player->query("level") < 20 ) return 0;
    if( !player->query("capsule_pill", 1) ) return 0;
    return 1;
}

// �������Ȫ�NPC  (�H�ɦW���ѧO)
string getAssigner() {
    return "/world/area/blood_wild/npc/pill.c";  // �s���k�Ĥs�m
}

// �������Ȯɪ��T��
string *getAssignMessage() {
    // $N��NPC, $n��player
    string *msg = ({
        CYN"$n�V$N�i���Ĥj�v���ƩM�M�ݦ�������ٵ�����...\n"NOR,
        "$N���D�G"HIG"����[�S����v�S�F�A�S�Q��L�~�M���D�ڦb�o�̡C\n"NOR,
        "$N���D�G"HIG"�����A���i�O�ں�߻s�@�����ġC\n"NOR,
        "$N���D�G"HIG"�Y�U�h���p����s�͡A�ҥH�ڥs�L�u���ͽ��n�v\n"NOR,
        "$N���D�G"HIG"�Q�n�ܡH�Q�n�N�h���ڷj���@�ǧڭn�����ë~�C\n"NOR
    });
    return msg;
}

// ���ȶ��n�����Y�ǩǪ��A�Y���ݭn�h return 0
mapping getKill() {
    return ([]);
}

// ���ȶ��n���o�Y�Ǫ��~�A�Y���ݭn�h return 0
// �`�N�G�o�Ǫ��~���ݬO�ƦX������~��
mapping getItem() {
    mapping item = ([
        "/world/area/wild/npc/item/snake_skin.c": 20,   // �D��
        "/world/area/muye/npc/eq/mouse_head.c": 5,      // ���Y
        "/world/area/old_forest/item/coal.c": 50,       // ���q
        "/world/area/old_forest/item/copper.c": 30,     // ���q
        "/world/area/old_forest/item/iron.c": 30,       // �K�q
        "/world/area/lake/npc/item/bell.c": 1,          // ������
    ]);
    return item;
}

// �������Ȫ����󰣤F�t�δ��Ѫ�
// 1. �j�����~
// 2. ���F�����ƶq���Ǫ����~
// ���ݭn���ܡA�٥i�H�ۭq�������ȱ���
// return 1, ����������, return 0;������
int postCondition(object player, object npc)
{
    return 1;
}

// �������Ȫ�NPC  (�H�ɦW���ѧO)
string getRewarder() {
    return "/world/area/blood_wild/npc/pill.c";  // �s���k�Ĥs�m
}

// �������Ȯɪ��T��
string *getRewardMessage() {
    // $N��NPC, $n��player
    string *msg = ({
        "$N���D�G"HIG"�S���I�N�O�o�ǪF��I\n"NOR,
        "$N���D�G"HIG"$n���������A�{�b���ڨӻs�@�ī~�C\n"NOR,
        "$N�h�W�a���D�G"HIG"���M�O���ġA���O���ٵL�k�����ī~���ĪG�C\n"NOR,
        "$N�h�W�a���D�G"HIG"�`�������X�ӴN�O�F�C\n"NOR,
    });
        
    return msg;
}

string getReward()
{
    string msg = RED"��"HIW"��"HIK"���n"NOR"�@�ɡC\n";
    return msg;
}

/*  ���ȼ��y
    ���y���ӯ�ۥѵo���A�p�G
        1. ��o�g��
        2. ��o���~
        3. ��o�u��Buff
        4. �߱o�Y�ޯ�
        5. ��缾�a���A, ex: ��¾
 */
void reward(object player, object npc) {
    object pill;

    switch( random(4) ) {
        case 0: pill = new("/world/capsule/_str.c"); break;
        case 1: pill = new("/world/capsule/_con"); break;
        case 2: pill = new("/world/capsule/_dex.c"); break;
        case 3: pill = new("/world/capsule/_int.c"); break;
    }
    message_vision(CYN"\n$N�N���Ʃ�i���������U�}���A�|�P�����ܦ�A�o�X�R�E�԰ժ��{�q�p���C\n"NOR, npc, player);
    if( pill->move(player) )
        message_vision(CYN"$N�����B�Y�W�����w�A�N"NOR+pill->query("name")+NOR+CYN"���X�V���a�浹$n�C\n\n"NOR, npc, player);
    else {
        // �]�����ĨC�ӵ��Ū��ݨD���~���P
        // �ҥH�����\���b�a�W����L�H��
        // �p�G���W�L���N���s�ĥ��Ѫ�������
        message_vision(HIR"�������M�F���@�n�A�N�|�P�����@���J�¡C\n\n"NOR, npc, player);
        destruct(pill);
    }
}
