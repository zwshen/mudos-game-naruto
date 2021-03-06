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
    switch( random(4) ) {
        case 0: this_object()->delete_temp("ticket_card");
                this_object()->set_temp("ticket_card/music", 1);
                command("perform lending ticket.guard" );
                break;
        case 1: this_object()->delete_temp("ticket_card");
                this_object()->set_temp("ticket_card/bow", 1);
                command("perform lending ticket.guard" );
                break;
        case 2: this_object()->delete_temp("ticket_card");
                this_object()->set_temp("ticket_card/ton", 1);
                command("perform lending ticket.attack on " + enemy->query_id() );
                break;
        case 3: this_object()->delete_temp("ticket_card");
                this_object()->set_temp("ticket_card/wheya", 1);
                command("perform lending ticket.attack on " + enemy->query_id() );
                break;
    }
}

void do_change()
{
    if( this_object()->query_condition("ticket", 1) != 0 && !this_object()->is_fighting() ) {
        this_object()->delete_condition("ticket");
    }
    if( this_object()->query_condition("ghost_change1", 1) != 0 ) return;
    command("perform change ability.change dex");
}

void create()
{
    set_name("克萊門斯", ({ "clemens" }) );
    set_race("human");
    set_level(60);
    set_class("hxh_star");  // 一星獵人
    set("age", 45);
    set("camp", "hunter");
    set("nickname", HIR"火箭人"NOR);
    set("long", "在魔術馬戲團中人氣最旺的明星，除了外表俊美吸引不少婦女前來\n"
                "觀看，他的飛人技術更是出神入化，各中空中表演只要眨眼間便完\n"
                "成，得到火箭人的稱呼，表演項目為空中飛人。可以利用train 指\n"
                "令來學習技能。使用 list 指令查詢可學習的技能列表。\n");

    set("chat_chance", 50);
    set("chat_msg", ({
        (: do_change :),
    }) );
    set("chat_chance_combat", 15);
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
    set_train_with_camp("combat", 1, 1, 120, "hunter", -2);           // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 200, "hunter", 0);             // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 140, "hunter", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 140, "hunter", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 160, "hunter", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 200, "hunter", -2);    // 連擊之術
    set_train_with_camp("special", 1, 10, 200, "hunter", -2);         // 特質系程度
    set_train_with_camp("holy hand", 0, 15, 140, "hunter", -1);       // 聖療之手
    set_train_with_camp("change ability", 0, 20, 120, "hunter", 0);   // 魂體轉換
    set_train_with_camp("lending ticket", 1, 21, 140, "hunter", 0);   // 借貸券

    setup();
    set_skill("combat", 120);
    set_skill("dodge", 200);
    set_skill("parry", 140);
    set_skill("heavy hit", 140);
    set_skill("savage hit", 160);
    set_skill("continual hit", 200);
    set_skill("special", 200);
    set_skill("holy hand", 200);
    set_skill("change ability", 200);
    set_skill("lending ticket", 200);
}
int accept_kill(object me, string arg)
{
    mapping cnd = ([]);

    if( this_object()->query_condition("ticket", 1) == 0) {

        cnd["name"] = HIW+"空中飛人"+NOR;
        cnd["duration"] = 900;
        cnd["from"] = this_object();
        this_object()->set_condition("ticket", cnd);

        do_chat( ({
            (: command, "say 寶貝們！這就叫空中飛人！" :),
        }) );
    } else {
        do_chat( ({
            (: command, "say 知道飛在空中的感覺嗎！" :),
        }) );
    }
}
int accept_fight(object me, string arg)
{
    return 0;
}
