/*  travel_muye.c
        
    write by Acme       - 2007.02.05
 */

#include <ansi.h>

void create() { seteuid(getuid()); }

// �������ɬO���ȡA�o�Ө禡���ݭn�ܰ�
int isQuest() { return 1; }

/* �����ȬO�_�୫�Ƹ�  return 0  ���୫��
                       return 1  �i����
   ��ĳ�̦n�]�w���୫�ơC
 */
int isNewly() { return 0; }

// ���ȦW��
string getName() {
    return "�A�ѧԪ�¾�~";
}

// ���ȴy�z
string getDetail() {
    string msg;
        
    msg  = "�p�G�A�Q�A�ѧԪ�¾�~�S�⪺�ܡA�A�i�H�h�бСu�Ԫ̾Ǯաv����|�d�C\n";
    msg += "��m�N�b�X�F�u�@�֩����]�v����n��A�A���ӫܮe���i�H��쪺�C\n";

    return msg;
}

// ���ȵ���
int getLevel() {
    return 1;
}

/* �������Ȫ��e�m����A�i��O
        1. ���ŻݨD
        2. ¾�~�ݨD
        3. �رڻݨD
        4. �w�����Y�ǥ��ȻݨD
    �����A���i�H�ۥѵo���~�O�C
    �^�ǫD�s�Ȫ��ܲŦX����C
 */
int preCondition(object player) {
    return 1;
}

// �������Ȫ�NPC  (�H�ɦW���ѧO)
string getAssigner() {
    return "/world/area/muye/npc/fooder.c";
}

// �������Ȯɪ��T��
string *getAssignMessage() {
    // $N��NPC, $n��player
    string *msg = ({
        "$N���$n���D�G�p�G�A�Q�A�ѧԪ�¾�~�S�⪺�ܡA�A�i�H�h�бСu�Ԫ̾Ǯաv����|�d�C\n",
        "$N���$n���D�G��m�N�b�X�F�u�@�֩����]�v����n��A�A���ӫܮe���i�H��쪺�C\n",
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
    return ([]);
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
    return "/world/area/muye/npc/ka.c";
}

// �������Ȯɪ��T��
string *getRewardMessage() {
    // $N��NPC, $n��player
    string *msg = ({
        "$N���$n���D�G�A�n�I\n",
        CYN"$N�r�֪��L���ۡC\n"NOR,
        "$N���$n���D�G�A�Q�A�ѧԪ̬O����ڡH\n",
        "$N���$n���D�G�Ԫ̴N�O�i�H�I�i�U�اԳN��¾�~�C\n",
        "$N���$n���D�G�ӧԳN�j���i�H���T�j���C\n",
        "$N���$n���D�G�Ĥ@�G�ԳN�A�ĤG�G�۳N�A�ĤT�G��N�C\n",
        "$N���$n���D�G�Q�����츭�����@���ܡH�ڭ̫D�`�w��A���u�[�J�v\n",
        "$N���$n���D�G�p�G�A�w�g�O�ڭ̤츭�����@���A�Q�ոէԪ̾Ǯաu���~�ҡv���ܡA�i�H��ڻ��C(���O�Gsay ���~��)\n",
    });
        
    return msg;
}

string getReward()
{
    return "�ǲ��I�� 20 �I";
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
    player->add_point("learn", 20);
    tell_object(player, HIY"(�A��o�F 20 �I�ǲ��I�ơC)\n"NOR);
}