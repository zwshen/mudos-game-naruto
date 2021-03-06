// mouse by 2007/7/31

inherit NPC;

#define LIFE 20000

void create()
{
    set_name("魔法假人", ({ "magic stake", "stake", "_OBJ_STAKE_" }) );
    set_race("human");
    set("long", "平常被用來測試新魔術的假人，擁有極高的抵抗力。\n");
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

// 玩家技能 combat 超過 120 級不接受攻擊 比木人高一些
int accept_fight(object ob) { if( ob->query_skill("combat", 1) > 120) return 0; else return 1; }

varargs int receive_damage(int damage, object from, object attacker)
{
    return damage;
}
