#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // 訓練導師

void do_fight()
{
    object enemy, sword, item;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( !objectp(sword = present("_CREATION_SWORD_", this_object())) ) {
        item = new("/daemon/skill/hxh/concrete/obj/sword_obj.c");
        item->move(this_object());
    }
    if( this_object()->query_condition("firewall") == 0 ) {
        command("perform fire wall.fire");
    } else {
        command("perform frost closed ball.ball on " + enemy->query_id() );
    }
    return;
}

void create()
{
    set_name("言峰����", ({ "yan feng", "feng", "yan" }) );
    set_race("human");
    set_level(70);
    set_class("hxh_star2");  // 二星獵人
    set("age", 46);
    set("camp", "hunter");
    set("nickname", HIM"魔術師"NOR);
    set("long", "善長以念力轉化為能量的能力，因為參加一項名為聖杯戰爭的遊戲\n"
                "而到處搜集其他參加者情報，還創辦「魔術馬戲團」將自己的念能\n"
                "力偽裝成魔術到處表演，其中不少團員都不知道他真正的目的。\n"
                "可以利用train 指令來學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n");

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
    set_train_with_camp("combat", 1, 1, 160, "hunter", -2);              // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 140, "hunter", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 160, "hunter", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 160, "hunter", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 140, "hunter", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 180, "hunter", -2);       // 連擊之術
    set_train_with_camp("variation", 1, 10, 200, "hunter", -2);          // 變化系程度
    set_train_with_camp("fire variation", 0, 15, 160, "hunter", -1);     // 火念力變化
    set_train_with_camp("ice variation", 0, 15, 160, "hunter", -1);      // 冰念力變化
    set_train_with_camp("electric variation", 0, 15, 160, "hunter", -1); // 電念力變化
    set_train_with_camp("frost closed ball", 0, 21, 140, "hunter", 0);   // 冰封球
    set_train_with_camp("chain lighting", 0, 21, 140, "hunter", 0);      // 連鎖閃電
    set_train_with_camp("fire wall", 1, 21, 140, "hunter", 0);           // 火牆

    setup();
    set_skill("combat", 160);
    set_skill("dodge", 140);
    set_skill("parry", 160);
    set_skill("heavy hit", 160);
    set_skill("savage hit", 140);
    set_skill("continual hit", 180);
    set_skill("variation", 200);
    set_skill("ice variation", 200);
    set_skill("frost closed ball", 200);
    set_skill("fire wall", 200);
}
int accept_fight(object me, string arg)
{
    return 0;
}
