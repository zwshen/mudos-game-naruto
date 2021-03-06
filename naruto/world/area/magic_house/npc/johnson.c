#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // 訓練導師

void do_fight()
{
    object enemy;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    // 破壞拳
    command("perform destory fist.attack on " + enemy->query_id() );
}
void create()
{
    set_name("藍迪強森", ({ "johnson" }) );
    set_race("human");
    set_level(60);
    set_class("hxh_star");  // 一星獵人
    set("age", 45);
    set("camp", "hunter");
    set("nickname", HIB"巨怪"NOR);
    set("long", "個頭異於常人的高大肌肉男，因為身上穿著緊身衣表現出完美的身\n"
                "型，原本是一位在工地裡的工人，後來被魔術馬戲團的人員發掘而\n"
                "加入，表演項目為健美先生。可以利用train 指令來學習技能。使\n"
                "用 list 指令查詢可學習的技能列表。\n");

    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // 只教導獵人
    set("guild", "hunter");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 200, "hunter", 0);            // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 120, "hunter", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 140, "hunter", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 200, "hunter", 0);         // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 140, "hunter", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 160, "hunter", -2);    // 連擊之術
    set_train_with_camp("strength", 1, 10, 200, "hunter", -1);        // 強化系程度
    set_train_with_camp("body strength", 0, 15, 160, "hunter", -1);   // 肉體強化
    set_train_with_camp("powerup", 1, 21, 200, "hunter", 0);          // 剛力
    set_train_with_camp("destory fist", 0, 20, 140, "hunter", 0);     // 破壞拳

    setup();
    set_skill("combat", 180);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("heavy hit", 200);
    set_skill("savage hit", 140);
    set_skill("continual hit", 160);
    set_skill("strength", 200);
    set_skill("body strength", 200);
    set_skill("powerup", 200);
    set_skill("destory fist", 200);
}
int accept_kill(object me, string arg)
{
    if( this_object()->query_condition("body_strength_cond", 1) == 0) {
        do_chat( ({
            (: command, "perform body strength.powerup" :),
            (: command, "say 看看吧！這健美的肌肉！" :),
        }) );
    } else {
        do_chat( ({
            (: command, "say 絕不能失去這份工作！" :),
        }) );
    }
}
int accept_fight(object me, string arg)
{
    return 0;
}
