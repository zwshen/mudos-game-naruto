#include <npc.h>
#include <ansi.h>

inherit F_TRAINER;         // 訓練忍者

void do_fight()
{
    int x, y, hit, damage, raiseDamage;
    object enemy, pet, ob, yaa;
    string msg;
    mapping cnd = ([]);

    // 沒有敵人
    enemy = this_object()->query_opponent();
    pet = this_object()->query_temp("pet");
    x = this_object()->query("area_info/x_axis");
    y = this_object()->query("area_info/y_axis");

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( !query_condition("four_foot") ) {
        command("perform four foot.beast");
        return;
    } else if( !query_condition("fang_cd") ) {
        switch( random(2) ) {
            case 0:  // 牙通牙
                if( !present("_PET_YAA_", environment(this_object())) ) {
                    command("perform double fang.atwirl on " + enemy->query_id() );
                    break;
                }
            case 1:  // 獸人分身，如果已經分身過就用牙狼牙
                if( pet ) {
                    destruct(pet);
                    yaa = new(__DIR__"yaa.c");
                    yaa->set_name(HIR"[赤]"NOR"犬塚牙", ({ "quan zhong yaa", "yaa", "_PET_YAA_" }));
                    yaa->set_temp("dog_quit", 1);
                    message_vision(CYN"\n$N臉上露出一抹勝利的微笑，兩手飛快結印，開始施展"HIR"『獸人分身』"NOR+CYN"之術！\n"NOR, this_object());
                    if( area_move(environment(this_object()), yaa, x, y) ) {
                        message_vision("只見"+this_object()->query("pet/name")+"「砰」地一陣煙霧後，居然變成了$N！\n\n"NOR, this_object());
                        yaa->kill_ob(enemy);
                        if( function_exists("accept_kill", enemy) && !enemy->is_killing(yaa) && enemy->accept_kill(yaa) ) return;
                        enemy->kill_ob(yaa);
                        message_vision("\n"NOR, this_object());
                    } else {
                        message_vision("但是什麼事情也沒有發生...\n\n"NOR, this_object());
                    }
                    break;
                }
            default:
                if( ob = present("_PET_YAA_", environment(this_object())) ) {
                    if( !area_environment(this_object(), ob) ) break;   // 不在同位不給用
                    if( this_object() == ob ) break;                    // 假的不准用
                    if( random(2) == 1 ) msg = "\n$n"HIC"轉身一躍至$N的身上，兩人開始一同快速結印施展"HIK"『"BLINK+HIR" 牙 "NOR+BLINK+RED"狼 "HIR"牙 "NOR+HIK"』"HIC"形成兩道強勁的颶風撲向目標！\n"NOR;
                    else msg = HIC"\n$N轉身一躍至$n"HIC"的身上，兩人開始一同快速結印施展"HIK"『"BLINK+HIR" 牙 "NOR+BLINK+RED"狼 "HIR"牙 "NOR+HIK"』"HIC"形成兩道強勁的颶風撲向目標！\n"NOR;
                    hit = this_object()->query_ability("exact");

                    this_object()->add_temp("apply/exact", hit)/2;
                    message_vision(msg, this_object(), ob);
                    if( !COMBAT_D->isHit(this_object(), enemy) ) {
                        message_vision("只是兩人使用了過多的力道，居然衝過頭在$N後方地上轟出深數十公尺的大洞！\n\n"NOR, enemy);
                    } else {
                        raiseDamage = 2200;

                        this_object()->add_temp("apply/attack", raiseDamage);
                        damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                        this_object()->add_temp("apply/attack", -raiseDamage);

                        if( damage < 1200 ) damage = random(400) + 800;

                        enemy->receive_damage(damage, this_object());
                        message_vision( sprintf("颶風一前一後地衝擊$n，直接刺穿$n的身子，形成兩個血窟窿(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                    }
                    this_object()->add_temp("apply/exact", -hit);
                    cnd["name"] = HIC+"(CD)狼牙"+NOR;
                    cnd["duration"] = 5;

                    this_object()->set_condition("fang_cd", cnd);
                }
                break;
        }
    }
    return;
}

void to_do_say()
{
    int i;
    object pet, ob;
    object *inv;

    inv = all_inventory(environment(this_object()));

    if( ob = present("_PET_YAA_", environment(this_object())) ) {
        if( this_object() != ob ) {
            message_vision(CYN"$N看四周沒有敵人，便讓$n"CYN"變回"+query("pet/name")+"了。\n"NOR, this_object(), ob);
            destruct(ob);
            command("perform animal taming.call");
        }
        return;
    }
    if( !objectp(pet = this_object()->query_temp("pet")) ) {
        add_temp("call_pet", 1);
        for(i=0;i<sizeof(inv);i++) {
            if( inv[i] == this_object() ) continue;
            if( !this_object()->visible(inv[i]) ) continue;
            if( userp(inv[i]) ) continue;
            if( environment()->is_area() && !area_environment(this_object(), inv[i])) continue;
            if( ob = present("_MY_PET_", environment(this_object())) ) {
                if( ob->query_owner() == this_object() ) {
                    delete_temp("call_pet");
                    i += sizeof(inv);
                }
            }
        }
        if( query_temp("call_pet") ) {
            command("perform animal taming.call");
        }
    } else if( pet->query_food() < 10 ) {
        pet->add_food(999);
        pet->set_name("赤丸", ({ "quan zhong yaa's dog", "dog" }));
        pet->set_level(60);
        pet->set("long", "犬塚牙的狗，看起來小小隻的十分可愛。\n");
        if( pet->query_stat_maximum("hp") != 12000 ) pet->set_stat_maximum("hp", 12000);
        pet->set_stat_maximum("ap", 3000);
        pet->set_stat_maximum("mp", 3000);
        pet->set_stat_current("hp", pet->query_stat_maximum("hp"));
        pet->set_stat_current("ap", pet->query_stat_maximum("ap"));
        pet->set_stat_current("mp", pet->query_stat_maximum("mp"));
        pet->set_attr("str", 120);
        pet->set_attr("con", 120);
        pet->set_attr("dex", 120);
        pet->set_attr("int", 120);
        pet->set_skill("combat", 200);
        pet->set_skill("parry", 200);
        pet->set_skill("dodge", 200);
        pet->set_skill("heavy hit", 200);
        pet->set_skill("savage hit", 200);
        pet->set_skill("continual hit", 200);
    } else if( pet->query_food() < 800 ) {
        pet->add_food(200);
    }
    do_heal();
    return;
}

void create()
{
    set_name("犬塚牙", ({ "quan zhong yaa", "yaa" }));
    set_race("human");
    set_level(50);
    set_class("middle");            // 中忍
    set("classify", "strengthen");  // 強化
    set("camp", "muye");
    set("long", "脾氣剛烈，以本能行動、充滿野性的木葉村忍者。屬於夕日紅小隊的\n"
                "成員。犬塚一家就如其名，一生都與忠犬一同行動，犬塚牙也是如此\n"
                "身旁的赤丸總是形影不離的跟著主人犬塚牙。\n");

    set("age", 16);
    set("gender", "male");

    set("chat_chance", 70);
    set("chat_msg", ({
        (: to_do_say :),
    }) );

    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    set("guild", "muye");
    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 140, "muye", -2);              // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 180, "muye", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 120, "muye", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 160, "muye", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 140, "muye", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 140, "muye", -2);       // 連擊之術
    set_train_with_camp("ninja", 1, 10, 160, "muye", -2);              // 忍術
    set_train_with_camp("force", 1, 10, 120, "muye", -2);              // 體術
    set_train_with_camp("animal taming", 0, 15, 140, "muye", -1);      // 忍術：馴獸術
    set_train_with_camp("double fang", 0, 20, 140, "muye", 0);         // 忍術：牙通牙
    set_train_with_camp("four foot", 1, 21, 120, "muye", 0);           // 忍術：四腳之術

    setup();
    set_skill("combat", 180);
    set_skill("continual hit", 200);
    set_skill("ninja", 200);
    set_skill("double fang", 200);
    set_skill("four foot", 200);
    set_skill("animal taming", 200);
    set_skill("substitute", 200);
    map_skill("dodge", "substitute");

    add_temp("apply/exact", 250);      // 命中
    add_temp("apply/evade", 150);      // 迴避
    add_temp("apply/intimidate", 50);  // 攻擊能力
    add_temp("apply/dex", 30);
}

void die()
{
    object enemy, killer;
    int i = 15 + random(16);
    string msg;

    enemy = this_object()->last_damage_giver();

    if( !enemy ) {
        destruct(this_object());  // 找不到對手，直接消失
        return;
    }

    if( query_temp("dog_quit") ) { // 寵物的牙 直接死掉
        ::die();
        return;
    }

    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = HIR"\n赤丸難過地在主人的屍體旁哀嚎...\n\n卻被"+enemy->query("name")+"一腳踹飛出去，只能躺在一旁哭泣...\n\n"NOR;
    msg += HIG"【"HIR"木葉快訊"HIG"】"HIG"因為牠的主人「"NOR+YEL"犬塚一族"HIG"」"+this_object()->query("name")+"已經被"+enemy->query("name")+"殺死再也無法站起來回應牠了...\n\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}

int accept_kill(object me, string arg)
{
    if( query_condition("four_foot") == 0) {
        message_vision("$N說道﹕"HIG"居然敢出手，四腳之術！\n"NOR, this_object());
        command("perform four foot.beast");
    } else {
        message_vision("$N說道﹕"HIG"居然敢出手，我們上！赤丸！\n"NOR, this_object());
    }
}
