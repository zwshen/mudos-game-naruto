#include <npc.h>

inherit F_VILLAGER;

object owner;

// 設定擁有者
int set_owner(object obj)
{
    if( !objectp(obj) ) return 0;
    owner = obj;
}

// 查詢擁有者
object query_owner()
{
    if( !objectp(owner) ) return 0;
    return owner;
}

// 刪除影分身
void do_destruct()
{
    // 已經要消失的寵物就不用一直喊要消失了
    if( query("WILL_DELETE") ) return;

    // 發現寵物召喚過多次會發生保護錯誤
    // 因為離開時沒有刪除寵物保護
    // 所以累積了過多的 guard 資訊  by mouse 2009/2/16
    this_object()->guard_ob(0);
    message_vision("$N就像蒸發似地慢慢消失在空中...\n", this_object());
    set("WILL_DELETE", 1);

    // 延遲讓一些動作先跑過
    do_chat( ({ (: destruct, this_object() :) }) );
    return;
}

// 隨時檢查擁有者是否有足夠查克拉，並且吸取
void do_check()
{
    // 擁有者消失，則影分身消失
    if( !objectp(owner) ) {
        do_destruct();
        return;
    }
    
    // 在不同位置也會消失
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), owner) ) {
            do_destruct();
            return;
        }
    } else {
        if( environment(this_object()) != environment(owner) ) {
            do_destruct();
            return;
        }
    }

    // 擁有者的查克拉不足
    if( owner->query_stat("mp") < query_level() ) {
        do_destruct();
        return;
    }

    if( query_stat("hp") < 10 ) {
        do_destruct();
        return;
    }

    // 擁有者消秏一些查克拉
    owner->damage_stat("mp", query_level() , owner);
    return;
}

// 死亡或昏倒時就準備消失 2007/7/25新增 by mouse
void unconcious()
{
    do_destruct();
    return;
}
void die()
{
    do_destruct();
    return;
}

// 是否接受命令
int accept_order(object who, string cmd)
{
    return 0;  // 分身是不受控制的
}

void create()
{
    set_name("家人", ({ "family", "__FAMILY_NPC__" }));
    set_race("beast");

    // 平時動作：檢查owner還在不在，並吸取其查克拉
    set("chat_chance", 3);
    set("chat_msg", ({
        (: do_check :),
    }));

    // 戰鬥時動作：檢查owner還在不在，並吸取其查克拉
    set("chat_chance_combat", 5);
    set("chat_msg_combat", ({
        (: do_check :),
    }) );

    set("no_fight", 1);
    setup();
}
