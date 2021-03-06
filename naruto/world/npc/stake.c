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

    // 戰鬥設定
    set("no_combat", 1); // 不能攻擊
    set("no_defend", 1); // 不能防禦
    set("no_evade", 1);  // 不能迴避
    
}

// 玩家技能 combat 超過一百級不接受攻擊
int accept_fight(object ob) { if( ob->query_skill("combat", 1) > 100) return 0; else return 1; }

varargs int receive_damage(int damage, object from, object attacker)
{
/* 打不爆 by -Acme-
    // 沒有攻擊者
    if( !attacker ) return 0;

    // 假人的生命 判斷
    add("stake_life",-damage);
    if( query("stake_life") < 0 ) {
        message_vision("「喀啦」數聲響，$N變成花花碎片，散落滿地了。\n",this_object());
        remove_all_killer();
        call_out( (:destruct($1):),1,this_object());
    }       
*/
    return damage;
}
