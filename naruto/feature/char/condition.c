/* condition.c 長效狀態
   create by Acme 20070329
*/

#include <condition.h>

mapping conditions = ([]);

// 從檔案取回長效狀態資料後，恢復長效狀態的影響。
void restore_condition()
{
    string cnd;
    mixed cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) )
        return;

    foreach(cnd, cnd_data in conditions)
        CONDITION_D(cnd)->condition_apply(this_object(), cnd, cnd_data);
}

// 每次心跳更新長效狀態
void update_condition()
{
    string cnd;
    mapping cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) ) return;

    foreach(cnd, cnd_data in conditions)
        CONDITION_D(cnd)->condition_update(this_object(), cnd, cnd_data);
}

// 刪除長效狀態
void delete_condition(string cnd)
{
    if( !mapp(conditions) || !sizeof(conditions) ) return;
    if( undefinedp(conditions[cnd]) ) return;

    
    CONDITION_D(cnd)->condition_unapply(this_object(), cnd, conditions[cnd]);
    map_delete(conditions, cnd);
}

// 清除所有長效狀態
void clear_condition()
{
    string cnd;
    mapping cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) ) return;

    foreach(cnd, cnd_data in conditions) {
        if( cnd_data["no_clear"] ) continue;  // 如果有不能刪除的功能就先不刪
        delete_condition(cnd);
    }
}

// 設定長效狀態
void set_condition(string cnd, mapping info)
{
    string key, *buff;

    if( !info || !mapp(info) ) return;
    if( !mapp(conditions) ) conditions = ([]);
    
    // 已經存在這個 condition, 則先移掉
    if( !undefinedp(conditions[cnd]) )
        delete_condition(cnd);

    buff = keys(info);
    conditions[cnd] = ([]);

    foreach(key in buff)
        conditions[cnd][key] = info[key];

    CONDITION_D(cnd)->condition_apply(this_object(), cnd, conditions[cnd]);
}

mapping query_condition(string cnd)
{
    if( !mapp(conditions) || !sizeof(conditions) ) return 0;
    if( undefinedp(conditions[cnd]) ) return 0;
    return conditions[cnd];
}

mapping query_all_conditions()
{
    return conditions;
}
