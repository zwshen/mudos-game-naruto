#include <npc.h>
#include <ansi.h>

inherit F_TRAINER;    // 訓練導師

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$N" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$N" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$N" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_fight()
{
    object enemy;
    int i;

    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( query_stat_current("hp") < query_stat_maximum("hp")/4 ) i = 6;
    else i = random(5) + 1;

    if( !enemy ) return;
    if( query_temp("asuri", 1) ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    switch( i ) {
        case 1: // 燒鬼斬
            command("perform fire ghost chop.attack on " + enemy->query_id() );
            break;

        case 2: // 二斬
            command("perform chop two.attack on " + enemy->query_id() );
            break;

        case 3: // 三十六煩惱鳳
            command("perform age agonize.attack on " + enemy->query_id() );
            break;

        case 4: // 獅子輓歌
            command("perform dirge lion.attack on " + enemy->query_id() );
            break;

        case 5: // 三千世界
            message_vision("\n$N"HIR"將二把武器拿在手上開始旋轉....四周的空氣似乎有點凝結...\n"NOR,this_object(), enemy);
            message_vision("\n"HIW"當"NOR"$N"HIW"發動攻擊時只見"NOR"$n"HIW"忽地抓住了"NOR"$N"HIW"的破綻，使出必殺絕招"HIY"『"HIR+BLINK"三千世界"NOR+HIY"』\n"NOR, enemy, this_object());
            message_vision("$N"HIW"只覺得意志忽然遭受重擊，眼前一白什麼也不知道了...\n"NOR, enemy, this_object());
            remove_all_killer();
            do_heal();
            enemy->unconcious();
            break;
        case 6:
            set_temp("asuri", 1);
            message_vision(HIK"\n$N身上發散出可怕的魔氣，居然化身為三頭六臂的魔神"NOR+MAG"『鬼氣•九刀流』\n"NOR,this_object(), enemy);
            call_out("asuri",5, this_object(), enemy);
            tell_object(enemy, HIR"你被索隆的氣勢所震，一時間無法行動！\n"NOR);
            enemy->start_busy(3);
            start_busy(2);
    }
}
void asuri(object ob, object enemy)
{
    int damage = ob->query_ability("attack")*2 + ob->query_ability("defend")*2 + random(1000);
    message_vision(HIK"\n$N用著鬼神般的回聲說道：\n\n『"NOR+MAG"苦難算什麼...\n\n\t我本就是走在"NOR+HIR"修羅之道"NOR+MAG"上的男人！"HIK"』\n\n\n"NOR+RED"三頭六臂的魔氣從四面八方攻擊"NOR"$n"RED"，令"NOR"$n"RED"根本無從閃避！"NOR"\n\n　　　　　『 "BRED"阿修羅"NOR"　　"HIC+BLINK"壹"HIK"•"NOR+BLINK+YEL"霧"HIK"•"HIW"銀"NOR" 』\n\n"NOR, ob, enemy);
    enemy->receive_damage(damage, ob);
    enemy->damage_stat("ap", damage/5, ob);
    enemy->start_busy(2);
    message_vision("$N"HIK"的"NOR+RED"鮮血"HIK"像湧泉般地灑向空中，濺在四周與$n的身上"NOR"("+damage+")"+report_status(enemy)+""HIR"被血與魔氣所籠罩的$n，看起來就像要將"NOR"$N"HIR"帶入修羅界的魔王...\n"NOR, enemy, this_object());
    do_heal();
    delete_temp("asuri");
    return;
}

void create()
{
    set_name("索隆", ({ "zoro" }) );
    set_race("human");
    set_level(60);
    set_class("reward_sea");  // 懸賞海賊
    set("age", 19);
    set("title", HIG"海賊獵人"NOR);
    set("long", "身上帶著三把刀的劍客，他就是著名的海賊獵人─羅羅諾亞•索隆\n"
                "，不過因為某些原因現在的他已經成為草帽海賊團的一員，還被世\n"
                "界政府重金懸賞。\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向索隆學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    // 接受過索隆的教學便加入海賊王部份
    // 至於選則海軍還是海賊並沒有影響
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 160, "robber", -2);           // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 140, "robber", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 180, "robber", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 140, "robber", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 200, "robber", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 120, "robber", -2);    // 連擊之術
    set_train_with_camp("blade", 1, 10, 200, "robber", -2);           // 刀術基礎
    set_train_with_camp("wolf blade", 1, 15, 140, "robber", -1);      // 刀術：刀狼流
    set_train_with_camp("ghost chop", 1, 15, 160, "robber", -1);      // 刀術：鬼斬
    set_train_with_camp("chivy tiger", 1, 15, 160, "robber", -1);     // 刀術：虎•狩獵
    set_train_with_camp("fire ghost chop", 0, 20, 140, "robber", 0);  // 刀術：燒鬼斬
    set_train_with_camp("chop two", 0, 30, 140, "robber", 1);         // 刀術：二斬
    set_train_with_camp("age agonize", 0, 40, 120, "robber", 2);      // 刀術：三十六煩惱鳳
    set_train_with_camp("dirge lion", 0, 40, 120, "robber", 2);       // 刀術：獅子輓歌

    set("set_drop", ({
        ([ "type":"wp", "id":66, "amount":1, "p1":1, "p2":500 ]),        // 三代鬼徹
        ([ "type":"wp", "id":68, "amount":1, "p1":1, "p2":500 ]),        // 雪走
        ([ "type":"wp", "id":63, "amount":1, "p1":1, "p2":800 ]),        // 和道一文字
    }) );

    setup();
    set_skill("combat", 180);
    set_skill("dodge", 180);
    set_skill("parry", 180);
    set_skill("heavy hit", 200);
    set_skill("savage hit", 200);
    set_skill("continual hit", 160);
    set_skill("blade", 200);
    set_skill("wolf blade", 200);
    set_skill("ghost chop", 200);
    set_skill("chivy tiger", 200);
    set_skill("fire ghost chop", 200);
    set_skill("chop two", 200);
    set_skill("age agonize", 200);
    set_skill("dirge lion", 200);
//  carry_object(__DIR__"wp/snow_blade.c")->wield();
//  carry_object(__DIR__"wp/ghost_blade.c")->wield("lefthand");
//  carry_object(__DIR__"wp/beta_blade.c");
    add_temp("apply/exact", 100);       // 命中
    add_temp("apply/evade", 100);       // 迴避
    add_temp("apply/intimidate", 150);  // 攻擊能力
    add_temp("apply/wittiness", 150);   // 防禦能力
    add_temp("apply/con", 15);
    add_temp("apply/str", 15);
}
int accept_kill(object me, string arg)
{
    if( this_object()->query_condition("bladewolf", 1) == 0) {
        message_vision("索隆說道﹕"HIG"讓我試刀嗎？有意思。\n"NOR, this_object());
        message_vision(CYN"索隆臉上露出邪惡的笑容﹐不知道哪裡想歪了。\n"NOR, this_object());
        do_chat( ({
            (: command, "perform wolf blade.flow" :),
        }) );
    } else {
        message_vision("索隆說道﹕"HIG"我答應過魯夫絕不能輸。\n"NOR, this_object());
    }
}
int accept_fight(object me, string arg)
{
    do_chat( ({
        (: command, "shake" :),
        (: command, "say 為了成為世界第一的大劍客，沒有時間跟"+me->query("name")+"切磋。" :),
    }) );
    return 0;
}
