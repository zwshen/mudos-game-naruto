// stake.c 假人 
// 2002/04/13 -Tmr
// update by -Acme-

inherit NPC;

#define LIFE 10000

void create()
{
    set_name("假人", ({ "wood stake", "stake", "_OBJ_STAKE_" }) );
    set_race("human");
    set("long", "一個木製的假人，專門給大家練功\用的。\n");
    // 假人的生命值
    set("stake_life", LIFE);
    setup();
    set_attr("str", 10);
    set_attr("con", 10);
    set_attr("dex", 10);
    set_attr("int", 10);
    delete_stat("hp");
}

// 玩家技能 combat 超過一百級不接受攻擊
int accept_fight(object ob) { if( ob->query_skill("combat", 1) > 100) return 0; else return 1; }

// 假人不會迴避
varargs int evade(int ability, object from) { return 0; }

// 假人無法防禦
varargs int defend(int damage, object from) { return damage; }

//假人不會攻擊
varargs int attack(object opponent) { return 0; }

varargs int receive_damage(int damage, object from, object attacker)
{
    // 沒有攻擊者
    if( !attacker ) return 0;

    // 假人的生命 判斷
    add("stake_life",-damage);
    if( query("stake_life") < 0 ) {
        message_vision("「喀啦」數聲響，$N變成花花碎片，散落滿地了。\n",this_object());
        remove_all_killer();
        call_out( (:destruct($1):),1,this_object());
    }       
    return damage;
}

