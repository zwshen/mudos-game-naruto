#include <npc.h>
#include <ansi.h>

inherit F_TRAINER;    // 訓練導師

void do_fight()
{
    object enemy;
    object* targets;
    int i, damage, raiseDamage, exact, evade;

    // 沒有敵人
    enemy = this_object()->query_opponent();
    targets = this_object()->query_enemy();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    // 當攻擊人數超過兩人改用群體技
    if( sizeof(targets) >= 2 ) {
        exact = COMBAT_D->exact(this_object(), enemy, 1)/2 + COMBAT_D->evade(this_object(), enemy, 1)*3/4;

        message_vision("\n$N的"HIY"卷卷眉"NOR"皺了起來怒道道："HIG"這群不懂規矩的傢伙，讓你們知道什麼叫餐桌禮儀！\n\n"NOR, this_object());
        message_vision(YEL"只見$N雙手撐地兩腳朝天，連續踢擊快速如風"NOR"『"BYEL"違反餐桌禮儀之踢"NOR"』"YEL"！\n"NOR, this_object());
        for(i=0;i<sizeof(targets);i++) {
            if( !userp(targets[i]) ) {
                message_vision(HIY"$N一腳正中$n的臉部，$n叫了一聲隨即暈死過去。\n"NOR, this_object(), targets[i]);
                remove_killer(targets[i]);
                targets[i]->unconcious();
            } else {
                evade = COMBAT_D->exact(targets[i], this_object(), 1);

                if( !COMBAT_D->SkillHit(this_object(), targets[i], exact, evade) ) {
                    message_vision(HIY"$N飛快地朝$n連續踢出三腿，但是都被$n僥倖閃過了。\n"NOR, this_object(), targets[i]);
                    this_object()->start_busy(1);
                } else {
                    raiseDamage = 1000;
                    add_temp("apply/attack", raiseDamage); 
                    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                    add_temp("apply/attack", -raiseDamage);
                    targets[i]->receive_damage(damage, this_object());
                    message_vision( sprintf(HIY"$N一腳踢中了$n的腰間，痛的$n說不出話來(%d) %s\n"NOR, damage, COMBAT_D->report_status(targets[i]) ), this_object(), targets[i]);
                    targets[i]->start_busy(1);
                }
            }
        }
    message_vision(YEL"\n$N收回了攻勢！\n\n"NOR, this_object());
    } else {
        // 粗碎
        command("perform shatter kick.attack on " + enemy->query_id() );
    }
    return;
}
void check_diabo()
{
    delete_condition("diabo_busy");  // 清除惡魔風腳的冷卻
    do_heal();
    return;
}
void create()
{
    set_name("香吉士", ({ "sanji" }) );
    set_race("human");
    set_level(60);
    set_class("reward_sea");        // 懸賞海賊
    set("classify", "strengthen");  // 強化
    set("age", 18);
    set("title", HIK"廚師"NOR);
    set("long", "一手做菜的好功夫，草帽海賊團裡人人都說讚。不過他可是聞名世\n"
                "界的大海賊─紅腳哲普的徒弟，除了做菜功夫，踢技也十分了得，\n"
                "在草帽海賊團中也算實力過人。\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向香吉士學習技能\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    set("chat_chance", 30);
    set("chat_msg", ({
        (: check_diabo :),
    }) );
    set("chat_chance_combat", 25);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // 接受過香吉士的教學便加入海賊王部份
    // 至於選則海軍還是海賊並沒有影響
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 140, "robber", -2);             // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 200, "robber", -2);              // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 160, "robber", -2);              // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 200, "robber", -2);          // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 160, "robber", -2);         // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 140, "robber", -2);      // 連擊之術
    set_train_with_camp("spurn", 1, 10, 200, "robber", -2);             // 踢技基礎
    set_train_with_camp("outfit kick", 1, 15, 160, "robber", -1);       // 踢技：踢技全餐
    set_train_with_camp("fried cold cuts", 1, 15, 140, "robber", -1);   // 踢技：油炸什錦拼盤
    set_train_with_camp("change face shot", 1, 21, 140, "robber", -1);  // 踢技：整型ＳＨＯＴ
    set_train_with_camp("diabolically foot", 0, 20, 120, "robber", 0);  // 踢技：惡魔風腳
    set_train_with_camp("shatter kick", 0, 40, 100, "robber", 2);       // 踢技：粗碎

    set("set_drop", ({
        ([ "type":"eq", "id":117, "amount":1, "p1":1, "p2":900 ]),      // 黑頭皮鞋
        ([ "type":"eq", "id":24, "amount":1, "p1":100, "p2":100 ]),     // 鍋子
    }) );
    setup();
    set_skill("combat", 180);
    set_skill("dodge", 180);
    set_skill("parry", 180);
    set_skill("heavy hit", 200);
    set_skill("savage hit", 200);
    set_skill("continual hit", 160);
    set_skill("spurn", 200);
    set_skill("outfit kick", 200);
    set_skill("fried cold cuts", 200);
    set_skill("change face shot", 200);
    set_skill("diabolically foot", 200);
    set_skill("shatter kick", 200);

    add_temp("apply/exact", 100);       // 命中
    add_temp("apply/evade", 150);       // 迴避
    add_temp("apply/intimidate", 150);  // 攻擊能力
    add_temp("apply/wittiness", 100);   // 防禦能力
    add_temp("apply/dex", 15);
    add_temp("apply/str", 15);

    carry_object(__DIR__"eq/shoes.c")->wear();
}
int accept_kill(object me, string arg)
{
    if( me->query("gender") == "female" ) {
        do_chat( ({
            (: command, "shake" :),
        }) );
        me->remove_killer(this_object());
        return 1;
    }         
    if( this_object()->query_condition("diabo_busy", 1) == 0) {
        command("perform diabolically foot.atwirl");
        message_vision("香吉士說道﹕"HIG"速戰速決！耽誤了娜美和小羅賓的吃飯時間我可不饒你。\n"NOR, this_object());
    } else {
        message_vision("香吉士說道﹕"HIG"打壞了我精心製作的食物可不饒你！\n"NOR, this_object());
    }
}
int accept_fight(object me, string arg)
{
    if( me->query("gender") == "female" ) {
        do_chat( ({
            (: command, "shake" :),
            (: command, "say 對待女士怎麼可以這樣。" :),
            (: command, "say 這有違我的騎士道精神。" :),
        }) );
        return 0;
    }   
    do_chat( ({
        (: command, "shake" :),
        (: command, "say 沒看到我在忙著做菜嗎！" :),
    }) );
    return 0;
}
void die()
{
    object enemy, killer;
    int i;
    string msg;

    enemy = this_object()->last_damage_giver();
    i = 70 + random(11);

    if( !enemy ) {
        destruct(this_object());  // 找不到對手，直接消失
        return;
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = "\n\n"YEL"\t香吉士"HIK"跪在地上用著最後一口氣說道："NOR"\n\n\t"HIB"『為了蔚藍海域...怎麼能在這時候就倒下...！』"NOR"\n\n\t"HIK"但是"NOR+YEL"香吉士"HIK"使盡了最後的力量還是無法戰勝對手"HIK"..."HIW"\n\n\t草帽海賊團廚師"HIK"「黑足」"NOR+YEL"香吉士"HIW"，被"HIR+enemy->query("name")+HIW"殺死了！"NOR"\n\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死香吉士獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
