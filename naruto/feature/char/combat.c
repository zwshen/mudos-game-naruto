/* combat.c
*/

#include <attack.h>
#include <dbase.h>
#include <score.h>
#include <skill.h>
#include <statistic.h>
#include <combat.h>

varargs int query_attr(string,int);

int ability_attack() { return query_attr("str") * 3 + query_temp("apply/attack"); }
int ability_defend() { return query_attr("con") * 3 + query_temp("apply/armor"); }
int ability_exact() { return query_attr("int")/2 + query_attr("dex")*3/2 + query_temp("apply/exact"); }
int ability_evade() { return query_attr("int")*3/2 + query_attr("dex")/2 + query_temp("apply/evade"); }
int ability_intimidate() { return query_attr("dex") + query_attr("str") + query_temp("apply/intimidate"); }
int ability_wittiness() { return query_attr("int") + query_attr("con") + query_temp("apply/wittiness"); }
int ability_carriage() { return query_attr("str") * 3000 + query_temp("apply/carriage") * 1000; }

/* 能力 */
varargs int query_ability(string application)
{
    if( !living(this_object()) ) return 0;

    switch(application) {
        case "attack": return ability_attack();          // 攻擊力
        case "defend": return ability_defend();          // 防禦力
        case "exact": return ability_exact();            // 命中能力
        case "evade": return ability_evade();            // 迴避能力
        case "intimidate": return ability_intimidate();  // 攻擊技巧
        case "wittiness": return ability_wittiness();    // 防禦技巧
        case "sock": return 1;                           // 致命一擊
        case "carriage": return ability_carriage();      // 負重能力
    }
    return 0;
}

// 接受攻擊
varargs int receive_damage(int damage, object from)
{
    int kill_mode = 0;
    mapping flag;
    string from_type;

    if( damage < 1 ) return 0;

    // 消耗體力
    damage_stat("hp", damage, from);

    // 比武模式
    if( !kill_mode && !from->is_killing(this_object()) && mapp(flag = query_exhausted()) && (flag["hp"] || flag["ap"] || flag["mp"]) ) {
        string stat;
        object ob;

        foreach(stat, ob in flag)
        set_stat_current(stat, 1);

        clear_statistic_flags();
        remove_all_enemy();

        call_out("lose_fight", 0, from);

        if( !userp(from) ) this_object()->unconcious();
        return damage;
    }

    return damage;
}
