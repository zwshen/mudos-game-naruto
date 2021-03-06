#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // 訓練導師

void do_fight()
{
    object enemy;
    int damage, raiseDamage , inti, i, exact, evade;

    // 沒有敵人
    enemy = this_object()->query_opponent();
    inti = COMBAT_D->intimidate(this_object(), 1);

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( (this_object()->query_stat_current("hp") < this_object()->query_stat_maximum("hp")/8)
        && !this_object()->query_condition("da") ) {
        command("perform digest absorb.check");
        return;
    }
    switch( random(3)+1 ) {
        case 1: // 嵐腳•蓮華
            command("perform kick lotus.kick on " + enemy->query_id() );
            break;
        case 2: // 毛髮束縛
            command("perform hair bind.tie on " + enemy->query_id() );
            break;
        case 3: // 指槍•Ｑ
            exact = inti + COMBAT_D->intimidate(this_object(), 1)/2;
            evade = COMBAT_D->wittiness(enemy, 1);

            message_vision("\n$N說道﹕"HIG"呦伊呦伊！柳•情•吟！\n\n"NOR, this_object());
            message_vision(HIR"$N右手舉起"NOR+YEL"禪杖"HIR"，左手食指拇指成圓圈起$n"HIR"位置，"HIM"「指槍•Ｑ」"HIR"禪杖穿過圓圈直刺$n"HIR"！\n"NOR, this_object(), enemy);
            if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
                message_vision("結果被$N閃過了，"NOR+YEL"禪杖"NOR"「碰」地一聲，只在地上刺出一個洞。\n\n"NOR, enemy);
                start_busy(1);
            } else {
                raiseDamage = 700;
                add_temp("apply/attack", raiseDamage); 
                damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/righthand"));
                add_temp("apply/attack", -raiseDamage);
                enemy->receive_damage(damage, this_object());
                message_vision( sprintf(HIY"$n"HIY"被鈍器的"NOR+YEL"禪杖"HIY"刺中，卻像是被刀劍刺穿身體一樣噴出血來！(%d) %s\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                // 擊中後有可能再追加四擊，一次命中比一次低
                for(i=0;i<4;i++) {
                    inti = inti/2;
                    exact = inti + COMBAT_D->intimidate(this_object(), 1)/2;

                    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
                        message_vision("$N又在同一地點使出"HIM"「Ｑ」"NOR"但是被"NOR"$n"NOR"閃過了，停下了攻勢。\n\n"NOR, this_object(), enemy);
                        return;
                        break;
                    } else {
                        raiseDamage = 550;
                        add_temp("apply/attack", raiseDamage); 
                        damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/righthand"));
                        add_temp("apply/attack", -raiseDamage);
                        enemy->receive_damage(damage, this_object());
                        message_vision( sprintf(HIY"$N一見勢不可擋，腳下一個"HIW"「月步」"HIY"換位，又刺出一記"HIM"「Ｑ」"HIY"正中"NOR"$n"HIY"！(%d) %s\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                    }
                }
                message_vision(HIR"\n$N收回了攻擊！\n\n"NOR, this_object());
            }
            return;
            break;
    }
}
void do_heal()
{
    if( (this_object()->query_stat_current("hp") < this_object()->query_stat_maximum("hp"))
        && this_object()->query_condition("da", 1) == 0) {
        command("perform digest absorb.check");
        return;
    }
    // 太吵了 讓機率再低一點
    if( random(100) < 1 ) {
        do_chat( ({ 
            (: command, "say 機關...！" :),
            (: command, "say 機關...！！" :),
            (: command, "say 機關...！！！" :),
            (: command, "say 可不能..." :),
            (: command, "say 隨便..." :),
            (: command, "say 亂碰的！...呦伊呦伊！" :),
            (: command, "say 要是...！" :),
            (: command, "say 要是...！！" :),
            (: command, "say 亂碰..." :),
            (: command, "say 別怪我..." :),
            (: command, "say 出手了！...呦伊呦伊！" :),
        }) );
    }
    // 隈取已經有補hp招，就不另外設定
    heal_stat("ap", 9999);
    heal_stat("mp", 9999);
}
void create()
{
    set_name("隈取", ({ "wei qu", "wei", "qu", "_WEI_" }) );
    set_race("human");
    set_level(60);
    set_class("guard_sea");         // 海軍校衛
    set("classify", "strengthen");  // 強化
    set("age", 25);
    set("title", HIR"ＣＰ９"NOR);
    set("long", "穿著一身和服，手上拿著一根金色手杖的男人，只見他獨自一人不停\n"
                "地以慢動作揮武手杖，跟著便哼起奇怪的小調，偶爾還會用身後的小\n"
                "鼓敲擊一聲然後拉長嗓音繼續高唱。\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向隈取學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    // 一般時動作
    set("chat_chance", 20);
    set("chat_msg", ({
        (: do_heal :),
    }) );
    set("chat_chance_combat", 25);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // 至於選則海軍還是海賊並沒有影響
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 180, "police", -2);           // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 120, "police", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 140, "police", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 140, "police", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 140, "police", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 140, "police", -2);    // 連擊之術
    set_train_with_camp("spurn", 1, 10, 160, "police", -2);           // 踢技基礎
    set_train_with_camp("kick haze", 1, 15, 140, "police", -1);       // 踢技：嵐腳
    set_train_with_camp("kick lotus", 0, 20, 140, "police", 0);       // 踢技：嵐腳•蓮華
    set_train_with_camp("digest absorb", 0, 20, 120, "police", 0);    // 特殊：消化吸收
    set_train_with_camp("hair bind", 0, 40, 100, "police", 1);        // 特殊：毛髮束縛

    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":10+random(31), "p1":100, "p2":100 ]),   // 黃金
        ([ "type":"wp", "id":81, "amount":1, "p1":1, "p2":100 ]),                  // 禪杖
    }) );
    setup();
    set_skill("combat", 180);
    set_skill("dodge", 180);
    set_skill("parry", 180);
    set_skill("heavy hit", 140);
    set_skill("savage hit", 140);
    set_skill("continual hit", 140);
    set_skill("spurn", 200);
    set_skill("kick lotus", 200);
    set_skill("hair bind", 200);
    set_skill("digest absorb", 200);
    set_skill("body iron", 140);
    set_skill("paper step", 140);

    add_temp("apply/exact", 100);       // 命中
    add_temp("apply/evade", 50);        // 迴避
    add_temp("apply/intimidate", 100);  // 攻擊能力
    add_temp("apply/wittiness", 50);    // 防禦能力
    add_temp("apply/str", 5);
    add_temp("apply/con", 10);
    add_temp("apply/dex", 5);
    add_temp("apply/int", 5);

    carry_object(__DIR__"wp/staff.c")->wield();
    carry_object(__DIR__"eq/pants.c")->wear();
    carry_object(__DIR__"eq/suit.c")->wear();
}
void die()
{
    object enemy, killer;
    int i;
    string msg;

    enemy = this_object()->last_damage_giver();
    i = 20 + random(11);

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
    msg = "\n\n"HIM+this_object()->query("name")+"被"+enemy->query("name")+"打的體無完膚，就這樣倒了下去！\n\n"NOR;
    msg += HIB"【世界政府】ＣＰ９「六式」高手"+this_object()->query("name")+"("+this_object()->query("id")+")居然被"+enemy->query("name")+"("+enemy->query("id")+")殺死了！\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死隈取獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
