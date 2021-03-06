/* update to 密室念魚 
 Tmr 2006/06/04
 Mouse 2007/7/25 修改
*/

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
    message_vision("$N甩了甩尾巴就消失在這個世界上了...\n", this_object());
    set("WILL_DELETE", 1);

    // 延遲讓一些動作先跑過
    do_chat( ({ (: destruct, this_object() :) }) );
    return;
}

// 隨時檢查擁有者是否有足夠查克拉，並且吸取
void do_check()
{
    string name;
    object ob;

    name = owner->query("id");
    ob = LOGIN_D->find_body(name);

    // 擁有者不在線上，則魚消失
    if( !ob ) {
        do_destruct();
        return;
    }
    // 在不同位置會自動移到主人旁邊，但是要消耗一些念力
    if( environment(owner)->is_area() ) {
        if( !area_environment(this_object(), owner) ) {
            area_move(environment(owner), this_object(), owner->query("area_info/x_axis"), owner->query("area_info/y_axis"));
            ob->damage_stat("mp", 5);
            message_vision("$N吸收了$n的念力重新回到$n身旁。\n", this_object(), owner);
            return;
        }
    } else {
        if( environment(this_object()) != environment(owner) ) {
            this_object()->move(environment(owner));
            ob->damage_stat("mp", 5);
            message_vision("$N吸收了$n的念力重新回到$n身旁。\n", this_object(), owner);
            return;
        }
    }
    if( owner->query_stat("mp") < 10 ) {
        message_vision("因為主人無法提供念力...$N漸漸消失了...\n", this_object(), owner);
        do_destruct();
        return;
    }
    return;
}

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
    set_name("密室念魚", ({ "fish", "__CHMABER_FISH_NPC__" }));
    set_race("beast");

    // 平時動作：檢查owner還在不在，並吸取其查克拉
    set("chat_chance", 100);
    set("chat_msg", ({
        (: do_check :),
    }));

    // 戰鬥時動作：檢查owner還在不在，並吸取其查克拉
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_check :),
    }) );

    set("no_fight", 1);
    setup();
}
