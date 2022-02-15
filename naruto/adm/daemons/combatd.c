/* combatd.c �԰����F
   create by Acme 2007.03.15
    �ץ����Z�� + enable �|�䤣��ԭz�����D by mouse 2007/7/25
*/

// #pragma save_binary
#include <ansi.h>

#define PI 3.14159265359

void create() { seteuid(getuid()); }

string *combat_actions = ({
    "$N�Τ⤤��$w��$n$l���h",
    "$N����$w�A��$n$l���h",
    "$N�N�⤤$w���$n$l���h",
    "$N���ʤ⤤$w�A��V$n$l",
    "$N�M�۪ŻءA�@�ӽb�B�W�e�⤤$w�K��$n$l����",
});

string *dodge_msg = ({
    "���O�M$p$l���F�X�o",
    "���O�Q$p���F�a���}�F",
    "���O$n���l�@���A�{�F�}�h",
    "���O�Q$p�ή��׶}",
    "���O$n�w���ǳơA���W���������}",
    "���O�S��",
});

string *parry_msg = ({
    "���O�Q$n��}�F",
    "���O�Q$n�צ�F",
});

// �̶ˮ`�{�סA���o���˰T��
string getDamageMessage(int damage)
{
    if( damage < 20 ) return "���G�u�O�j�j�y���@�B���L�ˮ`�I";
    if( damage < 40 ) return "���G�y�����L���ˮ`�I";
    if( damage < 80 ) return "���G�y���@�B�ˮ`�I";
    if( damage < 160 ) return "���G�y���@�B�Y���ˮ`�I";
    if( damage < 320 ) return "���G�y���ᬰ�Y�����ˮ`�I";
    if( damage < 640 ) return "���G�y���۷��Y�����ˮ`�I";
    if( damage < 1280 ) return "���G�y���̤��Y�����ˮ`�I";
    if( damage < 2560 ) return "���G�y�������Y�����ˮ`�I";
    return "���G�y���D�`�i�Ȫ��Y���ˮ`�I";
}

// ���o�H������O�Ȧ^��
string report_status(object me)
{
    int hp_max, ratio;
    
    if( !(hp_max = me->query_stat_maximum("hp")) ) return "";
    ratio = me->query_stat("hp")*100/hp_max;
    
    if( ratio >= 80 ) return HIK"["HIG + me->name() + HIG + ratio + "%" + HIK"]"NOR;
    else if( ratio >= 30 ) return HIK"["HIY + me->name() + HIY + ratio + "%" + HIK"]"NOR;
    else return HIK"["HIR + me->name() + HIR + ratio + "%" + HIK"]"NOR;
}

private int do_fight(object me, object target)
{
    if( !me || !target ) return 0;
    if( !living(me) || (userp(target) && !interactive(target)) ) return 0;
    if( !environment(me)  || !environment(target) ) return 0;

    if( environment(me)->is_area() ) {
        if( !area_environment(me, target) ) return 0;
    } else {
        if( environment(me) != environment(target) ) return 0;
        if( environment(me)->query("no_fight") ) return 0;
    }

    if( me->is_fighting(target) && target->is_fighting(me) ) return 0;
    
    me->kill_ob(target);
    if( userp(target) ) target->fight_ob(me);
    else target->kill_ob(me);
    
    return 1;
}

// ����
void start_hatred(object me, object obj)
{
    if( do_fight(me, obj) )
        message_vision( HIW"$N"HIW"�M$n"HIW"���H�ۨ����~�����A�ߨ襴�F�_�ӡI\n"NOR, me, obj);
}

// �@��
void start_vendetta(object me, object obj)
{
    if( do_fight(me, obj) )

        message_vision( HIW"$N"HIW"�M$n"HIW"���H�ۨ����~�����A�ߨ襴�F�_�ӡI\n"NOR, me, obj);
}

// �I��
void start_aggressive(object me, object obj)
{
    if( do_fight(me, obj) )
        message_vision( HIW"$N"HIW"�@����$n"HIW"�G�ܤ����A�ߨ�N���F�_�ӡI\n" NOR, me, obj);
}

void auto_fight(object me, object obj, string type)
{
    if( !userp(me) && !userp(obj) ) return;
    call_out( "start_" + type, 0, me, obj);
}

void start_camp_kill(object me, object obj, string msg)
{
    if( do_fight(me, obj) )
    
    message_vision(msg, me, obj);
}

void camp_auto_kill(object me, object obj, string msg)

{
    call_out("start_camp_kill", 0, me, obj, msg);
}

void announce(object me, string event)
{
    switch(event) {
        case "dead":
            message_vision("\n$N�D�u�F�X�n�A�y�X�@�f�A��A�K�_�F��C\n\n", me);
            break;
        case "unconcious":
            message_vision("\n$N�}�U�@�Ӥ�í�M�^�b�a�W�@�ʤ]���ʤF�C\n\n", me);
            break;
        case "revive":
            message_vision("\n$N�C�C�C�}�����M�M���F�L�ӡC\n\n", me);
            break;
    }
}

// �����ޥ�
int intimidate(object me, int type)
{
    int ability;

    string sk, *skills;
    
    if( !me ) return 0;
    
    ability = me->query_ability("intimidate");

    // ������Z���A�ޥ��n���C
    if( me->query_temp("weapon/twohanded") )
        ability = ability*7/10;

    skills = keys(me->query_skills());

    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("intimidate", SKILL_D(sk)) )
                ability = SKILL_D(sk)->intimidate(me, ability, type);
    }

    return ability;
}

// ���m�ޥ�
int wittiness(object me, int type)

{
    int ability;
    string sk, *skills;
    
    if( !me ) return 0;
    
    ability = me->query_ability("wittiness");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("wittiness", SKILL_D(sk)) )
                ability = SKILL_D(sk)->wittiness(me, ability, type);
    }
    
    return ability;
}

// �R���v
int exact(object me, object target, int type)
{
    int ability;
    string sk, *skills;

    
    if( !me || !target ) return 0;
    
    ability = me->query_ability("exact");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("exact", SKILL_D(sk)) )
                ability = SKILL_D(sk)->exact(me, target, ability, type);
    }
    
    return ability;
}

// �j�ײv
int evade(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    

    // �Q�]�w�S��k�j��
    if( me->query("no_evade") ) return 0;
    
    ability = me->query_ability("evade");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
       if( me->skill_mapped(sk) )
           if( function_exists("evade", SKILL_D(sk)) )
               ability = SKILL_D(sk)->evade(me, target, ability, type);
    }
    
    return ability;
}

// �Z�������O
int weapon_attack(object weapon, int damage, int use)
{
    int ability = damage;
    string type;

    if( stringp(type = weapon->query("equipped")) && type[0..6] == "weapon/" ) {
        mapping dam;

        type = type[7..];
        if( mapp(dam = weapon->query("damage/" + type)) ) {
            // �Z�����ˤO
            if( use ) ability = damage + dam["lower"] + random( dam["upper"] - dam["lower"] );
            else ability = damage + dam["lower"] + (dam["upper"]-dam["lower"])/2;
            // �[�����ˤO
            ability = ability * dam["bonus"] / 100;
        }
    }
    return ability - damage;
}

// �����O
int attack(object me, object target, int type, object weapon)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    // �H�����������O (��2�D�n�O�n������(heavy hit)�ɨ��t�@�b�������O)
    ability = me->query_ability("attack") / 2;

    // �Z���[��
    if( weapon && weapon->is_weapon() )
        ability += weapon_attack(weapon, ability, type);
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("attack", SKILL_D(sk)) )
                ability = SKILL_D(sk)->attack(me, target, ability, type);
    }
    
    return ability;
}

// ���m�O
int defend(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    

    // �Q�]�w�S��k���m
    if( me->query("no_defend") ) return 0;
    
    ability = me->query_ability("defend");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("defend", SKILL_D(sk)) )
                ability = SKILL_D(sk)->defend(me, target, ability, type);
    }
    
    return ability;
}

// �P�R�@��
int sock(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    ability = me->query_ability("sock");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("sock", SKILL_D(sk)) )
                ability = SKILL_D(sk)->sock(me, target, ability, type);
    }
    
    return ability;
}

// �P�R�@���ˮ`����%, ��l��(150%)
int sockPower(object me, object target, int type)
{
    int ability = 150;
    string sk, *skills;
    if( !me || !target) return ability;
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("sockPower", SKILL_D(sk)) )

                ability = SKILL_D(sk)->sockPower(me, target, ability, type);
    }
    
    return ability;
}

// ����ˮ`�e�A���ޯ���]�L receive_damage 
// �p��K�i�H�s�@ "�ȮɵL�ħ�" �άO "�ˮ`�l����" �������ޯ�
int receive_damage(object me, object target, int damage)
{
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("receiveDamage", SKILL_D(sk)) )
                damage = SKILL_D(sk)->receiveDamage(me, target, damage);
    }
    
    return damage;
}

// ���o�����T��
// �����T���� enable �b combat �ޯ�W���ޯണ��
// �Y�S enable �h�Ѿ԰��t�δ���
private string getCombatActions(object me, object weapon)
{
    string skill = me->skill_mapped("combat");
    // �S�� enable ����ޯ�
    if( !skill || skill == "combat" ) {
        if( weapon->query("have_mag") ) {
            if( weapon->is_weapon() ) return weapon->getCombatAction(me, weapon);
        }
        if( weapon->is_weapon() ) return combat_actions[random(sizeof(combat_actions))];
        else return RACE_D(me->query_race())->query_action();
    } else {
        if( weapon->query("have_mag") ) {
            if( weapon->is_weapon() ) return weapon->getCombatAction(me, weapon);
        }
        if( weapon->is_weapon() ) return combat_actions[random(sizeof(combat_actions))];
        else return SKILL_D(skill)->getCombatAction(me, weapon);
    }
}


// ���o�{���T��
// �����T���� enable �b dodge �ޯ�W���ޯണ��
// �Y�S enable �h�Ѿ԰��t�δ���
private string getEvadeActions(object me)
{
    string skill = me->skill_mapped("dodge");

    // �S�� enable ����ޯ�
    if( !skill || skill == "dodge" )
        return dodge_msg[random(sizeof(dodge_msg))];
    else return SKILL_D(skill)->getEvadeAction(me);
}

// ���o���m�T��
// �����T���� enable �b parry �ޯ�W���ޯണ��
// �Y�S enable �h�Ѿ԰��t�δ���
private string getDefendActions(object me)
{
    string skill = me->skill_mapped("parry");

    // �S�� enable ����ޯ�
    if( !skill || skill == "parry" )
        return parry_msg[random(sizeof(parry_msg))];

    else return SKILL_D(skill)->getDefendAction(me);
}

// �e�X�԰��T��
private void printMessage(string msg, object me, object target, object weapon)
{
    if( msg && stringp(msg) ) {
        string *limbs = target->query("limbs");
        if( !arrayp(limbs) || !sizeof(limbs) )
            msg = replace_string(msg, "$l", "���W");
        else
            msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
        if( weapon->is_weapon() )
            msg = replace_string(msg, "$w", weapon->name());
        message_vision(msg, me, target);
    }
}

// �`�A���G(Normal distribution) or �������G(Gaussian distribution)
// �i����j�O�i(Rick)�G�ڼg�U�� x=�쥻���ѷ��I    x*(sqrt(-2*log(rand))*cos(2*pi*rand)+2.5)
float normalDistribution(int value)
{
    float v, rand, result = 0;

    // int �ন float
    v = value;

    // random 0~1
    rand = random(1000000.0)/1000000.0;
    
    // ���i��random��0, ��log�|��, �]�����p��
    if( rand <= 0.0 ) rand = 0.0000001;

    result = v * (sqrt(-2*log(rand)) * cos(2*PI*rand) +2.5);

    return result;
}

// �R���B�z:  0. �S�R��, 1. �R��
int isHit(object me, object target)
{
    int chance, exact, evade;

    if( !living(target) ) return 1;
    if( target->query_stat("ap") < 1 ) return 1;
    
    exact = exact(me, target, 1);
    evade = evade(target, me, 1);
    
    // �Q�����H�O���a�A�h�P�_��ĤH�ƶq�A�L�h�|���C�j�ײv
    if( userp(target) ) {
        int move, amount;
        move = 4;
        amount = sizeof(target->query_enemy());
        if( amount > move ) evade -= (evade/10)*(amount-move);
    }
    
    // �������G
    return normalDistribution(exact) > normalDistribution(evade);
}

// �����ݭn�ݩR���� sk �ϥ�
int SkillHit(object me, object target, int meHit, int targetHit)
{
    int chance, exact, evade;

    if( !living(target) ) return 1;
    if( target->query_stat("ap") < 1 ) return 1;

    // �������G
    exact = normalDistribution(meHit);
    evade = normalDistribution(targetHit);

    if( exact > evade ) return 1;
    else return 0;
}

// �ˮ`�B�z: 0: �S���ˮ`, otherwise: ���ˮ`
int isDamage(object me, object target, object weapon)
{
    int chance, damage, defend;

    damage = attack(me, target, 1, weapon);

    if( !living(target) ) return damage;

    defend = defend(target, me, 1);

    // �Q�����H�O���a�A�h�P�_��ĤH�ƶq�A�L�h�|���C���m�O
    if( userp(target) ) {
    int move, amount;
        move = 4;
        amount = sizeof(target->query_enemy());
        if( amount > move ) defend -= (defend/10)*(amount-move);
    }

    // �S�����諸���m�Τ��i���m
    damage -= defend;
    chance = 50 + damage/2;

    if( damage < 0 ) damage = 0;

    if( chance < 10 ) chance = 10;
    else if( chance > 90 ) chance = 90;

    if( damage ) {    // �p�G�٦������O
        if( random(100) > chance ) return (damage/2)+random(damage/2)+1;  // ���o���\
        else return (damage*2/3) + random(damage/3)+1;                    // ���o�����\
    } else {          // �����O�����Q���
        if( random(100) > chance ) return 0;    // ���o�ܦ��\
        else return random(5)+1;                // ���o���Ӧ��\
    }
}

private int isFight(object me, object target, object weapon)
{
    if( !me || !target ) return 0;
    if( !weapon ) weapon = me;

    if( environment(me)->query("no_fight") && !target->query("unprotect_mark") && !me->query("unprotect_mark") )
        return 0;

    // �԰��L�{�_�u�A����԰�
    if( ( userp(me) && !interactive(me) ) || ( userp(target) && !interactive(target) ) )
        return 0;

    // �S�� ap �S��k����
    if( me->query_stat("ap") < 1 ) return 0;

    // �S��enable�԰��ޯ�A���|����
    if( !me->skill_mapped("combat") ) return 0;

    // �Q�]�w���������
    if( me->query("no_combat") ) return 0;

    return 1;
}

// ���`������
private int generalAttack(object me, object target, object weapon)
{
    int damage, sock;
    string msg;

    // �O�_����
    sock = (sock(me, target, 1) > random(100));

    // �]�w�����T��
    msg = (sock ? HIR"(�P�R�@��) "NOR : "") + getCombatActions(me, weapon) + "�A";
    
    // �S����
    if( !isHit(me, target) ) {
        // �Q�����̦� AP
        if( userp(me) ) target->damage_stat("ap", 1, target);

        // ��X�԰��T��
        msg += getEvadeActions(target) + "�C\n";
        printMessage(msg, me, target, weapon);
        return 0;
    }
    
    // �S���Ͷˮ`
    if( !(damage = isDamage(me, target, weapon)) ) {
        // ��X�԰��T��
        msg += getDefendActions(target) + "�C\n";
        printMessage(msg, me, target, weapon);
        return 0;
    }

    // �����ˮ`�O�p��
    if( sock ) damage = damage * sockPower(me, target, 1) / 100;

    // �����̦� AP
    if( userp(me) || (me->query_owner() && userp(me->query_owner())) )
        me->damage_stat("ap", random(damage/10) + 1, me);

    // �����ˮ`
    damage = receive_damage(target, me, damage);
    target->receive_damage(damage, me);

    // ��ܶˮ`�{��
    msg += getDamageMessage(damage) + "(" + damage + ")";
    // ��ܳQ�����̪��A
    msg += " " + report_status(target) + "\n";
    // ��ܾ԰��T��
    printMessage(msg, me, target, weapon);

    return 1;
}


// �۰ʬI�i���ޯ�B�z
private int autoCasting(object me, object target, object weapon)
{
    string sk, *skills;
    
    if( !me || !target ) return 0;

    if( !weapon || !weapon->is_weapon() )
        weapon = 0;
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("autoCasting", SKILL_D(sk)) )
                SKILL_D(sk)->autoCasting(me, target, weapon);
    }
}

int fight(object me, object target, object weapon)
{
    // �ˬd�O�_�����
    if( !isFight(me, target, weapon) ) return 0;

    // ���`����
    generalAttack(me, target, weapon);

    // �۰ʬI�i��
    autoCasting(me, target, weapon);

    return 1;
}
