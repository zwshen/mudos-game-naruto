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
 *  取得某一項基本數值。
 *
 *  每一個基本數值都由三個數字來定義：
 *
 *目前值 (current)
 *狀態值 (effective)
 *上限值 (maximum)
 *
 *  因為各種人物的生命型態不同，這三個數字可能有未定義的狀態。
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

/*  取得基本數值的資訊
 */
int query_stat_current(string what)
    { return mapp(st_current) ? st_current[what] : 0; }
    
int query_stat_maximum(string what)
    { return mapp(st_maximum) ? st_maximum[what] + this_object()->query_temp("apply/"+what) : 0; }
    
int query_stat_notify(string what)
    { return mapp(st_notify) ? st_notify[what] : 0; }
    
mixed query_stat_regenerate(string what)
    { return mapp(st_regenerator) ? st_regenerator[what] : 0; }

/*  設定基本數值
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
 *  設定基本數值的更新方式。
 */

mixed set_stat_regenerate(string what, mixed val)
{
    int max;

    /* 如果這個基本數值的最大值未定義，則不能設定更新方式。 */
    if( !(max = query_stat_maximum(what)) ) return 0;

    if( functionp(val) ) return (st_regenerator[what] = val);

    switch(val) {
        // 這項基本數值是不會自動更新的
        case TYPE_STATIC: return (st_regenerator[what] = 0);
    
        // 這項基本數值是會隨時間自動恢復的
        case TYPE_HEALTH:
            if( undefinedp(query_stat_current(what)) ) set_stat_current(what, max);
                return (st_regenerator[what] = (: health_regenerator :) );

        // 這項基本數值是會隨時間慢慢減少的
        case TYPE_WASTING:
            if( undefinedp(query_stat_current(what)) ) set_stat_current(what, max);
                return (st_regenerator[what] = (: wasting_regenerator :) );

        default: error("undefined regenerate method.\n");
    }
    return 0;
}

/* 初始化人物的基本數值 */

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

    /* 若未指定這個傷害來自哪一個生物，使用以下規則猜測 */
    if( !objectp(who) ) {
        if( this_player() ) who = this_player();
        else if( previous_object() && previous_object()->is_character() ) who = previous_object();
        else who = this_object();
    }

    /* 如果這種基本數值不存在，直接返回以節省時間 */
    if( !mapp(st_current) || undefinedp(st_current[type]) || f_exhausted[type] ) return 0;

    // 傷害是 hp 才有可能導致死亡
    if( type == "hp" && (who != this_object()) ) last_from_ob = who;
    
    st_current[type] -= damage;

    /* 若這個基本數值的目前值已經耗盡，設定記號等 heart_beat 時處理 */
    if( st_current[type] < 0 ) {
        st_current[type] = 0;
        f_exhausted[type] = who;
    }

    /* 若低於設定警示的百分比，設定記號等 heart_beat 時處理 */
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
 *  基本數值的更新函式。在人物的 heart_beat 中每當一個 tick 的時間到
 *  了，就會呼叫這個函式來更新人物的基本數值。
 *
 *  當人物的所有基本數值被設定的更新函式都傳回 0 的時候，regenerate
 *  會自動把自己關掉，直到 start_regenerate 被呼叫為止。
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

// 隨著時間恢復
//int health_regenerator(object me, string stat, int max, int eff, int cur)
int health_regenerator(object me, string stat, int max, int cur)
{
    if( me->is_fighting() ) return 0;   // 戰鬥中不會恢復

    // 當怪物沒有受到攻擊時，體力快速回復
    // 避免玩家有藥吃，怪物無藥可吃的過大差距
    // 寵物也不能有快速回復的能力
    if( !userp(me) && !me->query_owner() ) {
        if( cur < max )
            return me->heal_stat(stat, me->query_stat_maximum(stat));
        return 0;
    }
    // 恢復目前值
    // 因為技能影響有可能變成負值屬性，所以除法就發生錯誤，加點東西 by mouse 2009/6/6
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

// 隨著時間減少
int wasting_regenerator(object me, string stat, int max, int cur)
{
    if( !userp(me) ) return 0;
    return me->damage_stat(stat, 1 + (me->is_fighting() ? 2 : 0), me);
}
