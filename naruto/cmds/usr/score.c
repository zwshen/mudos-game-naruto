/* score.c
*/

// #pragma save_binary

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string hp_bar = "__________________________________________________";
string display_attr(int gift, int value);
string status_color(int value, int color_kind);
string show_score(object ob);
string show_bar(object ob, string entry);

int main(object me, string arg)
{
    object ob, eq;
    mapping wielded_weapon, buffering;
    string line, tmp, sk, buf;
    string wp1=HIK"--"NOR, wp1_c=HIK"--"NOR, wp2=HIK"--"NOR, wp2_c=HIK"--"NOR;
    string eq1="", eq1_c="", eq2="", eq2_c="";
    int exp;

    if( !arg ) ob = me;
    else {
    if( arg == "_MY_PET_" ) {
        if( !objectp(ob = me->query_temp("pet")) ) 
                return notify_fail("�A���G�S���Ԥ�...\n");
    } else ob = present(arg, environment(me));
        if(!ob) ob = find_player(arg);
        if(!ob) ob = find_living(arg);
        if( !ob ) ob = LOGIN_D->find_body(arg);
        if(!ob) return notify_fail("�A�n��ݽ֪����A�S\n");
        if(!living(ob)) return notify_fail("�A�u���ݥͪ������A�C\n");
        if( !wizardp(me) && (object)ob->query_owner() != me )
            return notify_fail("�u���Ův���ݧO�H�����A�C\n");
    }
    seteuid(getuid(ob));

    line = sprintf(NOR"�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n");
    line = sprintf("%s�x"HIW"�i%|8s�j"NOR" %-55s�x\n",line, ob->rank(), ob->short(1) );
    line = sprintf("%s�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);
    line = sprintf("%s�x%-68s\n",line,
    "���� " + HIC+ob->query("level")+NOR + " ��  " +
    "�~�� " + HIM+ob->query("age")+NOR + " ��  " +
    "�ر� " + HIY+to_chinese(ob->query_race())+NOR + "  " +
    "�ʧO " + HIG+((tmp = ob->query("gender")) ? to_chinese(tmp) : "�H�H")+NOR );

    line = sprintf("%s�u�w�w�w�w�w�w�w�w�s�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);

    // �����O�q
    exp = 0;
    exp = COMBAT_D->attack(ob, ob, 0, ob);
    
    wielded_weapon = ob->query_temp("weapon");
    if( mapp(wielded_weapon) && sizeof(wielded_weapon) ) {
        object weapon;
        string skill;
        foreach(skill, weapon in wielded_weapon) {
        if( skill[0..8] == "twohanded")      // ����Z��
        wp1 = wp1_c = wp2 = wp2_c = weapon->name();
        else if( skill[0..9] == "lefthand" )   // ����Z��
        wp2 = wp2_c = weapon->name();
        else wp1 = wp1_c = weapon->name();       // �k��Z��
            exp += COMBAT_D->weapon_attack(weapon, 0, 0);
        }
    }

    line = sprintf("%s�x�O�q  %-10s�x �����O�q %-5d  ���m�O�q %-5d  �ǲ��I�� %-8d�x\n",line,
        display_attr(ob->query_attr("str",1), ob->query_attr("str")),
        exp, COMBAT_D->defend(ob, ob, 0), ob->query_point("learn")
        );

    line = sprintf("%s�x���  %-10s�x �����ޥ� %-5d  ���m�ޥ� %-5d  �ݩ��I�� %-8d�x\n",line,
        display_attr(ob->query_attr("con",1), ob->query_attr("con")),
        COMBAT_D->intimidate(ob, 0),
        COMBAT_D->wittiness(ob, 0),
        ob->query_point("attribute")
    );
    
    line = sprintf("%s�x�ӱ�  %-10s�x �R����O %-5d  �j�ׯ�O %-5d  �ޯ��I�� %-8d�x\n",line,
        display_attr(ob->query_attr("dex",1), ob->query_attr("dex")),
        COMBAT_D->exact(ob, ob, 0),
        COMBAT_D->evade(ob, ob, 0),
        ob->query_point("skill")
    );
    

    line = sprintf("%s�x���z  %-10s�x �P�R�@�� %-5s  �P�R�ˮ` %-5s  ����I�� %-8d�x\n",line,
        display_attr(ob->query_attr("int",1), ob->query_attr("int")),
        COMBAT_D->sock(ob, ob, 0) + "%",
        COMBAT_D->sockPower(ob, ob, 0) + "%", 
        ob->query_point("score") );
    
    line = sprintf("%s�u�w�w�w�w�w�w�w�w�r�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);

    if( ob->query_stat_maximum("ap") ) {
        line = sprintf("%s�x��O��%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("ap")*100/ob->query_stat_maximum("ap"), 0),
            ob->query_stat("ap"),
            ob->query_stat_maximum("ap"),
            show_bar(ob, "ap")
        );
    }

    if( ob->query_stat_maximum("hp") ) {
        line = sprintf("%s�x��O��%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("hp")*100/ob->query_stat_maximum("hp"), 0),
            ob->query_stat("hp"),
            ob->query_stat_maximum("hp"),
            show_bar(ob, "hp")
        );
    }

    if( ob->query_stat_maximum("mp") ) {
          line = sprintf("%s�x��q��%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("mp")*100/ob->query_stat_maximum("mp"), 0),
            ob->query_stat("mp"),
            ob->query_stat_maximum("mp"),
            show_bar(ob, "mp") );
    }

    line = sprintf("%s�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);
    
    if( objectp(eq = ob->query_temp("armor/head_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    wp1 = uncolor(wp1);
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[�Y��]__"NOR+BLU"   �i�i�i   "HIK"__[�k��]"NOR" %-19s�x\n", eq1, wp1);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, wp1, wp1_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/face_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/wrist_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
//    tmp = sprintf("�x%19s "HIK"[�y��]__"NOR+BLU"   �i�i�i   "HIK"__[���]"NOR" %-19s�x\n", eq1, eq2);
    tmp = sprintf("�x%19s "HIK"[�y��]__"NOR+BLU"   "NOR+BBLU" o"BLU"�i"NOR+BBLU"o "NOR"   "HIK"__[���]"NOR" %-19s�x\n", eq1, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/neck_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/hand_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[�V��]__"NOR+BLU"   "BLK+BBLU"�c"WHT"�t"BLK"�c"NOR+BLU" �m"HIK"__[�ⳡ]"NOR" %-19s�x\n", eq1, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/cloth")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/armor")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[��A]__"NOR+BLU" �f�i�i�i"BLK+BBLU"�c"NOR+HIK" __[�Z��]"NOR" %-19s�x\n", eq1, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/finger_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/waist_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[���]__"NOR+BLU" �m  �i     "HIK"__[�y��]"NOR" %-19s�x\n", eq1, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/pants")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq2 = uncolor(eq2);
    wp2 = uncolor(wp2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[����]__"NOR"   "BLK+BBLU"�m"HIR+BBLU"�T"NOR+BLU"�m   "HIK"__[�Ǥl]"NOR" %-19s�x\n", wp2, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq2, eq2_c);
    tmp = replace_string(tmp, wp2, wp2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/leg_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/feet_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // ���εL�C�⪺���ƦC(�p����X�~���|�Q��i�h�ɭP�ñ�)
    tmp = sprintf("�x%19s "HIK"[�L��]__"NOR+BLU" �e�i  �i�e "HIK"__[����]"NOR" %-19s�x\n", eq1, eq2);
    // �N�L�C�⪺�m�������C�⪺
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    line = sprintf("%s�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);
    
    exp = 0;
    buffering = ob->query_all_conditions();
    if( sizeof(buffering) ) {
    foreach(buf in keys(buffering) ) {
    tmp = "";
        if( undefinedp(buffering[buf]) ) continue;
        exp++;
        sk = uncolor(buffering[buf]["name"]);
        if( exp == 1 ) tmp += "�x";
        tmp += sprintf("%-23s", sk + "("+ buffering[buf]["duration"]/30 + ":" + (buffering[buf]["duration"]*2)%60 + ")");
        tmp = replace_string(tmp, sk, buffering[buf]["name"]);
        if( exp%3 == 0 ) {
        exp = 0;
        tmp += "\n";
        }
        line += tmp;
    }
    if( exp%4 != 0 ) line += "\n";
    }
    line = sprintf("%s���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n",line);
    write(line);
    return 1;
}

string show_score(object ob)
{
    string msg;
    msg = to_chinese(ob->query("life_form"));
    if( ob->query_all_condition() ) {
        string condition;
        foreach( condition in keys(ob->query_all_condition()) ) {
            msg+=to_chinese(condition);
        }
    }
    return msg;
}

string display_attr(int gift, int value)
{
if( value > gift )
return sprintf( HIC "%3d%-7s" NOR, value, " (+" + (value - gift) + ")" );
else if( value < gift )
return sprintf( HIB "%3d%-7s" NOR, value, " (" + (value - gift) + ")" );
else
return sprintf( CYN "%3d       " NOR, value);
}

string show_bar(object ob, string entry)
{
    int cur, eff, max;
    cur = ob->query_stat_current(entry);
    max = ob->query_stat_maximum(entry);
    return sprintf("%s%s"NOR,
               status_color((cur*100/max), 1) + hp_bar[0..(cur*50/max)] + NOR,
               HIK + hp_bar[(cur*50/max)+1..49]);
}

string status_color(int value, int color_kind)
{       
    if( color_kind ) {
        switch( value ) {
            case  0..30: return BRED;
            case 31..80: return BYEL;
            case 81..100: return BGRN;
            default: return BCYN;
        }
    } else {
        switch( value ) {
                case  0..30: return HIR;
                case 31..80: return HIY;
                case 81..100: return HIG;
                default: return HIC;
        }
    }
}

int help(object me)
{
    write(@HELP
���O�榡 : score �� sc
           score <��H�W��>

�o�ӫ��O�i�H��ܧA(�p)�Ϋ��w��H(�t�Ǫ�)���򥻸�ơA�p�G�A����H
���O�A���Ԥ��A�L�k�ϥγo�ӫ��O�A�A�]�i�H�Q�� score _MY_PET_ �Ӷi
��d�ߡC
HELP
);
    return 1;
}
