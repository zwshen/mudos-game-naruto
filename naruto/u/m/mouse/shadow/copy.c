#include <npc.h>
#include <ansi.h>

// inherit F_VILLAGER;

object owner;
int attack = 0;        // 可攻擊與否
int evade = 0;         // 可迴避與否

void set_attack(int i) { attack = i; }
void set_evade(int i) { attack = i; }

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}

// 攻擊
varargs int attack(object opponent)
{
    if( !attack ) return 0;
    return ::attack(opponent);
}
// 迴避
varargs int evade(int ability, object from)
{
        if( !evade ) return 0;
        return ::evade(ability, from);
}
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
    message_vision("$N的身子漸漸淡化了...\n", this_object());
    set_heart_beat(0);
    destruct(this_object());
    return;
}
void do_check()
{
    // 擁有者消失，則複製品消失
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
    return;
}
void die()
{
    int damage;
    object enemy;
    enemy = this_object()->query_opponent();
    damage = 100+random(201);
    message_vision("$N微微的顫抖著，全身發出"HIW"激烈的白光"NOR"！\n", this_object(), enemy);
    message_vision("        $N身子瞬間炸開散出念勁，擊中了$n。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    return;
}
// 是否接受命令
int accept_order(object who, string cmd)
{
    return 0;  // 複製品是不受控制的
}
void create()
{
    set_name("庫嗶", ({ "kube" }));
    set_race("beast");

    // 平時動作：檢查主人還在不在
    set("chat_chance", 3);
    set("chat_msg", ({
        (: do_check :),
    }));
    // 戰鬥時動作：檢查主人還在不在
    set("chat_chance_combat", 5);
    set("chat_msg_combat", ({
        (: do_check :),
    }) );
    setup();
}
