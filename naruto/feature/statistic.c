/*  statistic.c

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
#include <login.h>
#include <move.h>
#include <statistic.h>

// variables

nosave int regenerating = 1;

mapping st_maximum = ([]);
mapping st_current = ([]);
mapping st_notify = ([]);
mapping st_point = ([]);
mapping st_quest = ([]);

nosave mapping st_regenerator;
nosave object last_from_ob;
nosave mapping f_exhausted = ([]);
nosave mapping f_destroyed = ([]);
nosave mapping f_notified = ([]);

// implementations

string* query_stat_name() { return mapp(st_maximum) ? keys(st_maximum) : ({}); }
object last_damage_giver() { return last_from_ob; }
mapping query_exhausted() { return f_exhausted; }
mapping query_destroyed() { return f_destroyed; }
mapping query_notified() { return f_notified; }

void clear_statistic_flags()
{
    f_exhausted = ([]);
    f_destroyed = ([]);
    f_notified = ([]);
}

int query_point(string what)
{
if( mapp(st_point) && !undefinedp(st_point[what]) ) return st_point[what];
}

void add_point(string what, int value)
{
    if( mapp(st_point) ) st_point[what] += value;
}

mapping query_all_quest()
{
    return st_quest;
}

int query_quest(string what, int id)
{
    if( mapp(st_quest) && !undefinedp(st_quest[what]) ) 
        return st_quest[what][id];
}

void add_quest(string what, int id, int value)
{
    if( undefinedp(st_quest[what]) ) st_quest[what] = ([]);
        st_quest[what][id] += value;
}

int delete_quest(string what, int id)
{
    if( !mapp(st_quest) && undefinedp(st_quest[what]) ) return 1;
    map_delete(st_quest[what], id);
    if( !sizeof(st_quest[what]) ) map_delete(st_quest, what);
    return 1;
}
/*  query_stat()
 *
 *  ���o�Y�@���򥻼ƭȡC
 *
 *  �C�@�Ӱ򥻼ƭȳ��ѤT�ӼƦr�өw�q�G
 *
 *�ثe�� (current)
 *���A�� (effective)
 *�W���� (maximum)
 *
 *  �]���U�ؤH�����ͩR���A���P�A�o�T�ӼƦr�i�঳���w�q�����A�C
 */
int query_stat(string what)
{
    int val;
    if( mapp(st_current) && !undefinedp(val=st_current[what]) ) return val;
    if( mapp(st_maximum) && !undefinedp(val=st_maximum[what]) ) return val;
    return 0;
}

void delete_stat(string what)
{
    if( mapp(st_current) )map_delete(st_current, what);
    if( mapp(st_maximum) )map_delete(st_maximum, what);
    if( mapp(st_notify) )map_delete(st_notify, what);
    if( mapp(st_regenerator) )map_delete(st_regenerator, what);
}

/*  ���o�򥻼ƭȪ���T
 */
int query_stat_current(string what)
    { return mapp(st_current) ? st_current[what] : 0; }
    
int query_stat_maximum(string what)
    { return mapp(st_maximum) ? st_maximum[what] + this_object()->query_temp("apply/"+what) : 0; }
    
int query_stat_notify(string what)
    { return mapp(st_notify) ? st_notify[what] : 0; }
    
mixed query_stat_regenerate(string what)
    { return mapp(st_regenerator) ? st_regenerator[what] : 0; }

/*  �]�w�򥻼ƭ�
 */
int set_stat_current(string what, int val)
//    { if( val > 9999 ) return 0; return mapp(st_current) ? st_currentwhat = val : 0; }
    { return mapp(st_current) ? st_current[what] = val : 0; }

int set_stat_maximum(string what, int val)
//    { if( val > 9999 ) return 0; return mapp(st_maximum) ? st_maximumwhat = val : 0; }
    { return mapp(st_maximum) ? st_maximum[what] = val : 0; }

int set_stat_notify(string what, int val)
//    { if( val > 9999 ) return 0; return mapp(st_notify) ? st_notifywhat = val : 0; }
    { return mapp(st_notify) ? st_notify[what] = val : 0; }

int advance_stat(string what, int val)
{
    if( !mapp(st_maximum) || undefinedp(st_maximum[what]) ) return 0;
    return set_stat_maximum(what, (st_maximum[what]+val));
}

/*  set_stat_regenerate()
 *
 *  �]�w�򥻼ƭȪ���s�覡�C
 */

mixed set_stat_regenerate(string what, mixed val)
{
    int max;

    /* �p�G�o�Ӱ򥻼ƭȪ��̤j�ȥ��w�q�A�h����]�w��s�覡�C */
    if( !(max = query_stat_maximum(what)) ) return 0;

    if( functionp(val) ) return (st_regenerator[what] = val);

    switch(val) {
        // �o���򥻼ƭȬO���|�۰ʧ�s��
        case TYPE_STATIC: return (st_regenerator[what] = 0);
    
        // �o���򥻼ƭȬO�|�H�ɶ��۰ʫ�_��
        case TYPE_HEALTH:
            if( undefinedp(query_stat_current(what)) ) set_stat_current(what, max);
                return (st_regenerator[what] = (: health_regenerator :) );

        // �o���򥻼ƭȬO�|�H�ɶ��C�C��֪�
        case TYPE_WASTING:
            if( undefinedp(query_stat_current(what)) ) set_stat_current(what, max);
                return (st_regenerator[what] = (: wasting_regenerator :) );

        default: error("undefined regenerate method.\n");
    }
    return 0;
}

/* ��l�ƤH�����򥻼ƭ� */

void init_statistic(mapping base)
{
    mapping st;
    string s;
    int val;

    if( mapp(st = query("statistic/maximum")) ) {
        st_maximum = st;
        delete("statistic/maximum");
    }

    if( mapp(st = query("statistic/current")) ) {
        st_current = st;
        delete("statistic/current");
    }

    if( mapp(st = query("statistic/notify")) ) {
        st_notify = st;
        delete("statistic/notify");
    }

    if( mapp(st = query("statistic")) ) delete("statistic");

    if( !mapp(st_maximum) ) st_maximum = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_current) ) st_current = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_notify) ) st_notify = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_regenerator) ) st_regenerator = allocate_mapping(NUM_STATISTICS);

    if( mapp(base) && sizeof(base) )
        foreach(s, val in base)
            if( undefinedp(st_maximum[s]) ) st_maximum[s] = val;
}

varargs int damage_stat(string type, int damage, object who)
{
    if( damage < 0 ) error("damage less than zero.\n");
    if( damage == 0 ) return 0;

    /* �Y�����w�o�Ӷˮ`�Ӧۭ��@�ӥͪ��A�ϥΥH�U�W�h�q�� */
    if( !objectp(who) ) {
        if( this_player() ) who = this_player();
        else if( previous_object() && previous_object()->is_character() ) who = previous_object();
        else who = this_object();
    }

    /* �p�G�o�ذ򥻼ƭȤ��s�b�A������^�H�`�ٮɶ� */
    if( !mapp(st_current) || undefinedp(st_current[type]) || f_exhausted[type] ) return 0;

    // �ˮ`�O hp �~���i��ɭP���`
    if( type == "hp" && (who != this_object()) ) last_from_ob = who;
    
    st_current[type] -= damage;

    /* �Y�o�Ӱ򥻼ƭȪ��ثe�Ȥw�g�ӺɡA�]�w�O���� heart_beat �ɳB�z */
    if( st_current[type] < 0 ) {
        st_current[type] = 0;
        f_exhausted[type] = who;
    }

    /* �Y�C��]�wĵ�ܪ��ʤ���A�]�w�O���� heart_beat �ɳB�z */
    if( who && mapp(st_notify) && !undefinedp(st_notify[type])) {
        if( mapp(st_maximum) && !undefinedp(st_maximum[type]) &&
            st_maximum[type] > 0 &&
            st_current[type]*100/query_stat_maximum(type) < st_notify[type] )
            //st_current[type]*100/st_maximum[type] < st_notify[type] )
            f_notified[type] = who;
    }
    start_regenerate();
    return damage;
}

int heal_stat(string type, int heal)
{
    int old_stat;

    if( heal < 0 ) error("heal less than zero.\n");

    if( !mapp(st_current) || undefinedp(st_current[type]) ) return 0;

    old_stat = st_current[type];
    st_current[type] += heal;

    if( mapp(st_maximum) && st_current[type] > query_stat_maximum(type) )
    st_current[type] = query_stat_maximum(type);

    start_regenerate();
    return st_current[type] - old_stat;
}

// start_regenerate()
//
// This function starts regenerating manually. The regenerating is on by
// default when characters inherits F_STATISTIC was created. It can be
// turned off by regenerate() eventually. If you want force regenerating
// to start, call this function.
void start_regenerate() { regenerating = 1; }

/*  regenerate()
 *
 *  �򥻼ƭȪ���s�禡�C�b�H���� heart_beat ���C��@�� tick ���ɶ���
 *  �F�A�N�|�I�s�o�Ө禡�ӧ�s�H�����򥻼ƭȡC
 *
 *  ��H�����Ҧ��򥻼ƭȳQ�]�w����s�禡���Ǧ^ 0 ���ɭԡAregenerate
 *  �|�۰ʧ�ۤv�����A���� start_regenerate �Q�I�s����C
 */

int regenerate()
{
    string st;
    mixed regenerator;
    int n_updated = 0;

    if( !regenerating ) return 0;

    if( !mapp(st_regenerator) || !mapp(st_maximum) ) return 0;

    foreach(st, regenerator in st_regenerator) {
        if( evaluate( regenerator, this_object(), st, query_stat_maximum(st), mapp(st_current) ? st_current[st] : 0) )
            n_updated++;
        if( mapp(st_current) && st_current[st] < 0 && !f_exhausted[st])
            f_exhausted[st] = this_object();
    }

    return regenerating = (n_updated > 0);
}

// �H�ۮɶ���_
//int health_regenerator(object me, string stat, int max, int eff, int cur)
int health_regenerator(object me, string stat, int max, int cur)
{
    if( me->is_fighting() ) return 0;   // �԰������|��_

    // ��Ǫ��S����������ɡA��O�ֳt�^�_
    // �קK���a���ĦY�A�Ǫ��L�ĥi�Y���L�j�t�Z
    // �d���]���঳�ֳt�^�_����O
    if( !userp(me) && !me->query_owner() ) {
        if( cur < max )
            return me->heal_stat(stat, me->query_stat_maximum(stat));
        return 0;
    }
    // ��_�ثe��
    // �]���ޯ�v�T���i���ܦ��t���ݩʡA�ҥH���k�N�o�Ϳ��~�A�[�I�F�� by mouse 2009/6/6
    if( cur < max ) {
        switch(stat) {
            case "ap": if( (int)me->query_attr("dex") > 4 ) return me->heal_stat(stat, (int)me->query_attr("dex")/5 );
                       else return me->heal_stat(stat, 1);
            case "hp": if( (int)me->query_attr("con") > 4 ) return me->heal_stat(stat, (int)me->query_attr("con")/5 );
                       else return me->heal_stat(stat, 1);
            case "mp": if( (int)me->query_attr("int") > 4 ) return me->heal_stat(stat, (int)me->query_attr("int")/5 );
                       else return me->heal_stat(stat, 1);
            default:   return me->heal_stat(stat, 10);
        }
    }
    if( cur > max ) {
        switch(stat) {
            case "ap": return me->set_stat_current(stat, max);
            case "hp": return me->set_stat_current(stat, max);
            case "mp": return me->set_stat_current(stat, max);
            default:   return me->set_stat_current(stat, max);
        }
    }
    return 0;
}

// �H�ۮɶ����
int wasting_regenerator(object me, string stat, int max, int cur)
{
    if( !userp(me) ) return 0;
    return me->damage_stat(stat, 1 + (me->is_fighting() ? 2 : 0), me);
}
