#include <npc.h>
#include <ansi.h>

object owner;

void create()
{
    set_name("蟑螂", ({ "cockroach" }) );
    set_race("beast");
    set_level(1);
    set("long", "一隻噁心的蟑螂。\n");
    set("limbs", ({ "蟑頭", "身體", "腹部", "蟑腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊

    set("set_drop", ({
        ([ "type":"obj", "id":25, "amount":1, "p1":80, "p2":100 ]),   // 蟑螂觸角
        ([ "type":"food", "id":34, "amount":1, "p1":60, "p2":100 ]),   // 蟑螂卵
        ([ "type":"obj", "id":26, "amount":1, "p1":80, "p2":100 ]),   // 蟑螂腳
    }) );
    setup();
}

// 設定主人
int set_owner(object obj)
{
    if( !objectp(obj) ) return 0;
    owner = obj;
}

// 查詢主人
object query_owner()
{
    if( !objectp(owner) ) return 0;
    return owner;
}

// 有人打強怪喜歡招一堆蟑螂去擋
// 但是保護戰鬥並不會將人打死
// 導致暈倒的蟑螂醒來後又是一個好盾牆
// 所以暈倒應該直接消失，避免又被使用
void unconcious()
{
    die();
    return;
}

void die()
{
    // 已經要死掉就不用一直講話了
    if( query("WILL_DIE") ) return;

    if( !query("no_die") ) {
        ::die();
        return;
    }
    message_vision("$N忽然說："HIG"$N的養育之恩我只能報答到此了！再見！\n"NOR, this_object(), owner);
    message_vision(CYN"$N一溜煙地就逃走了。\n"NOR, this_object());
    this_object()->guard_ob(0);
    if( owner ) {
        if( owner->query_temp("cockroach/guard") <= 1 ) owner->delete_temp("cockroach/guard");
        else owner->add_temp("cockroach/guard", -1);
    }
    set("WILL_DIE", 1);
    do_chat((: destruct, this_object() :));  // 延遲，讓被擊中傷害先跑出來
    return;
}
