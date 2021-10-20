/*  skill.c
 
    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>
 
    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.
 
    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>
#include <dbase.h>
#include <skill.h>

mapping skills          = ([]);         // �ޯ൥��
mapping learned         = ([]);         // �ޯ�g��

mapping skill_map       = ([]);         // The links of mapped skill.
mapping skill_flag      = ([]);         // Ultra skill flags.

mapping skill_ability   = ([]);			// �ޯ��I��
mapping skill_require   = ([]);			// �ޯ�ɯũһݸg��

string best_skill = "";

string query_best_skill()
{
    return best_skill;
}

mapping query_skills()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
        return copy(skills);
    return skills;
}

mapping query_skill_flags()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
        return copy(skill_flag);
    return skill_flag;
}

int query_skill_abandon(string skill)
{
    if( skill_flag[skill] & SKILL_FLAG_ABANDONED )
        return 1;
    else
        return 0;
}

mapping query_learned()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
        return copy(learned);
    return learned;
}

mapping query_skill_map()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
        return copy(skill_map);
    return skill_map;
}

void set_skills(mapping sk)
{
    if( sk ) skills = sk;
}

void set_skill(string skill, int val)
{
    if( val > 200 )
        val = 200;
    skills[skill] = val;
}

int set_learn(string skill, int lrn)
{
    return learned[skill] = lrn;
}

int delete_skill(string skill)
{
    string s1, s2;

    map_delete(skills, skill);
    map_delete(learned, skill);
    map_delete(skill_ability, skill);
    map_delete(skill_require, skill);

    foreach(s1, s2 in skill_map) if( s2==skill )
        map_delete(skill_map, s1);

    return 1;
}

///////////////////////////////////
// �ޯ��I�Ƭ����禡
///////////////////////////////////
// �d�ߩҦ��ޯ��I��
mapping query_skills_ability()
{
    return skill_ability;
}

// �]�w�ޯ��I��
int set_skill_ability(string skill, int v)
{
    if( v > 10 )
        v = 10;
    skill_ability[skill] = v;
    return 1;
}

// �֥[�ޯ��I��
int add_skill_ability(string skill)
{
    if( undefinedp(skill_ability[skill]) )
        set_skill_ability(skill, 0);
    skill_ability[skill] += 1;
    if( skill_ability[skill] > 10 )
        skill_ability[skill] = 10;
    return 1;
}

// �d�ߧޯ��I��
int query_skill_ability(string skill)
{
    if( undefinedp(skill_ability[skill]) )
        return 0;
    return skill_ability[skill];
}

// �R���ޯ��I��
int delete_skill_ability(string skill)
{
    if( undefinedp(skill_ability[skill]) )
        return 1;
    map_delete(skill_ability, skill);
    return 1;
}

///////////////////////////////////
// �ޯ�ɯũһݸg������禡
///////////////////////////////////
mapping query_skills_require()
{
    return skill_require;
}

// �]�w�ޯ�ɯũһݸg���
int set_skill_require(string skill, int exp)
{
    skill_require[skill] = exp;
    return 1;
}

// �d�ߧޯ�ɯũһݸg���
int query_skill_require(string skill)
{
    if( undefinedp(skill_require[skill]) )
        return 0;
    return skill_require[skill];
}

// �R���ޯ�ɯũһݸg���
int delete_skill_require(string skill)
{
    if( undefinedp(skill_require[skill]) )
        return 1;
    map_delete(skill_require, skill);
    return 1;
}

varargs void map_skill(string skill, string mapped_to)
{
    if( !mapped_to )
    {
        map_delete(skill_map, skill);
        return;
    }

    if( mapped_to=="none" )
        skill_map[skill] = 0;
    else if( mapped_to==skill )
        map_delete(skill_map, skill);
    else
        skill_map[skill] = mapped_to;
}

string skill_mapped(string skill)
{
    return !undefinedp(skill_map[skill]) ? skill_map[skill] : skill;
}

varargs int query_skill(string skill, int raw)
{
    int s;

    if( raw )
        return skills[skill];

    s = query_temp("apply/" + skill);
    if( undefinedp(skill_map[skill]) )
        s += skills[skill];
    else
    {
        if( skill_map[skill]==0 )
            return 0;
        s += (skills[skill] + query_skill(skill_map[skill]) ) / 2;
    }
    return s;
    //    return (s > 200) ? 200 : s;
}

int query_learn(string skill)
{
    return learned[skill];
}

nosave mapping skill_gain = ([]);

mapping query_skill_gain()
{
    return skill_gain;
}
void reset_skill_gain()
{
    skill_gain = ([]);
}

varargs void advance_skill(string skill, int amount)
{
    if( !amount )
        amount = 1;

    // �ޯ�g���k�s
    learned[skill] = 0;

    tell_object(this_object(), HIY"�A���ޯ� " + to_chinese(skill) + "(" + skill + ") ���Ŵ��ɦ� " + (skills[skill] + 1) + " �ŤF�C\n"NOR);

    if( undefinedp(skills[skill]) )
        skills[skill] = amount;
    else
        skills[skill] += amount;

    if( skills[skill] > 200 )
        skills[skill] = 200;

    // �I�s�ӧޯ�ɯŨ禡���䥦�B�z
    SKILL_D(skill)->skill_advanced(this_object(), skill);

    if( skills[skill] > skills[best_skill] )
        best_skill = skill;
}

varargs void improve_skill(string skill, int amount)
{
    if( skill_flag[skill] & SKILL_FLAG_ABANDONED )
        return;

    if( !amount )
        amount = 1;

    // �S���ޯ��I�ơA����W�[�g��
    if( undefinedp(skill_ability[skill]) )
        return;

    // �S���ޯ�ɯŸg��ݨD�A�ϥιw�]���ɯũһݸg��
    if( undefinedp(skill_require[skill]) )
        skill_require[skill] = skills[skill] * skills[skill] * 20;

    // �ޯ��I�Ƥ����A����W�[�g��
    if( skill_ability[skill] * 20 <= skills[skill] )
        return;

    // �̵��Ū����C�Ӧ����P���g�紣��
    amount = amount * (this_object()->query_level());

    if( undefinedp(learned[skill]) )
        learned[skill] = amount;
    else
        learned[skill] += amount;

    if( undefinedp(skill_gain[skill]) )
        skill_gain[skill] = amount;
    else
        skill_gain[skill] += amount;

    if( undefinedp(skills[skill]) )
        skills[skill] = 0;

    // �I�s�ӧޯ�ǲߨ禡���䥦�B�z
    SKILL_D(skill)->skill_improved(this_object(), skill);

    // �g�稬���ɯ�
    if( learned[skill] > skill_require[skill] )
        advance_skill(skill, 1);
}

varargs void abandon_skill(string skill, int restore)
{
    if( undefinedp(learned[skill]) )
        return;

    if( restore )
        skill_flag[skill] &= (~SKILL_FLAG_ABANDONED);
    else
        skill_flag[skill] |= SKILL_FLAG_ABANDONED;

    if( !skill_flag[skill] )
        map_delete(skill_flag, skill);
}

int query_skill_map_num()
{
    mapping my_skill_map;
    mixed *levels;

    my_skill_map = this_object()->query_skill_map();
    if( !mapp(my_skill_map) )
        return 0;
    levels = values(my_skill_map);
    levels -= ({ 0 });
    return sizeof(levels);
}

void clear_flags()
{
    skill_flag = ([]);
}
