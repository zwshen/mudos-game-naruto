#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;
inherit F_TRAINER;    // 訓練導師

string *door = ({ HIW"開門"NOR, HIR"休門"NOR, HIC"生門"NOR, NOR+YEL"傷門"NOR, 
                  HIG"杜門"NOR, HIB"景門"NOR, HIK"死門"NOR, REV"驚門"NOR });

int i = 0;

void do_fight()
{
    string msg;
    object enemy;
    int j, damage, raiseDamage;
    mapping cnd = ([]);

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( query_condition("soft_cd") ) return;
    if( is_busy() ) return;

    // 八門遁甲開門敘述統一在這
    // 小李目前能開五門，三到五門都可以使用�婼炸�
    if( (i == 1 || i > 3) && random(5) < 2 ) {
        set_temp("eight_pe", 1);
    } else if( i == 0 && random(10) > 6 ) {
        set_temp("lion_pe", 1);
    } else {
        if( i < 5 ) message_vision(HIR"\n$N雙手握拳，將全身的查克拉集中在周身大穴..."NOR"\n$N說道﹕"HIG"八門遁甲 第"HIY+chinese_number(i+1)+HIG"門•"+door[i]+HIG"，開！！\n\n"NOR, this_object());
    }
    if( i == 5 ) set_temp("eight_pe", 1);
    if( i > 3 && query_temp("eight_pe", 1) ) {
        j = i;
        if( i != 5 ) i = 5;
    }
    switch( i ) {
        case 0:  // 開門 - 表蓮華，獅子連彈
            if( !query_temp("lion_pe") ) {
                msg = HIG"只見$N額頭上冒出青筋，身體似乎充滿了力量。\n\n"NOR;
            } else {
                raiseDamage = 500;
                add_temp("apply/attack", raiseDamage);
                message_vision("\n$N說道﹕"HIG"讓$n"HIG"瞧瞧我青春熱血的厲害∼\n", this_object(), enemy);
                message_vision(HIY"\n$N使出一招"HIG"「影舞葉」"HIY"將$n"HIY"踢上空中，接著使出連續攻擊技"NOR+YEL"『青春爆發』\n"NOR, this_object(), enemy);
                for(j=0;j<4;j++) {
                    COMBAT_D->fight(this_object(), enemy, this_object());
                }
                add_temp("apply/attack", -raiseDamage);
                message_vision("\n", this_object());

                cnd["name"] = HIR+"(CD)連彈"+NOR;
                cnd["duration"] = 5;

                set_condition("soft_cd", cnd);
                delete_temp("lion_pe");
            }
            break;
        case 1:  // 休門 - 查克拉補滿
            if( !query_temp("eight_pe") ) {
                msg = HIG"$N身上查克拉含量正以異常快的速度回復中！\n\n"NOR;
                this_object()->set_stat_current("mp", query_stat_maximum("mp"));
            } else {
                message_vision("\n$N忽然間加快速度一記"HIG"「影舞葉」"NOR"將$n踢至空中，接著雙腳蹬地躍向$n！\n"NOR, this_object(), enemy);
                if( !COMBAT_D->isHit(this_object(), enemy) ) {
                    message_vision("但是$n在空中一個轉身，就這樣順利避開了$N的突襲。\n"NOR, this_object(), enemy);
                } else {
                    raiseDamage = 1000;

                    add_temp("apply/attack", raiseDamage); 
                    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                    add_temp("apply/attack", -raiseDamage);

                    if( damage < 400 ) damage = random(200) + 200;

                    enemy->receive_damage(damage, this_object());
                    message_vision( sprintf("$n被$N牢牢抓住"HIR"『表•蓮華』"NOR"快速從空中撞向地面，將$n撞的血肉糢糊！(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                }
            }
            break;
        case 2:  // 生門
            msg = HIG"$N身上所含的查克拉量已經超出身體存量，開始溢出體外造成天搖地動！\n\n"NOR;
            break;
        case 3:  // 傷門 - 加速體力回復 (使用海賊的消化吸收buff)
            msg = HIG"溢出體外的查克拉快速包圍$N的傷口，居然使$N體力異常快速回復！\n\n"NOR;

            cnd["name"] = HIR+"八門-傷"+NOR;
            cnd["duration"] = query_skill("eight shell", 1);
            cnd["hp"] = query_stat_maximum("hp")/50;

            set_condition("da", cnd);
            break;
        case 4:  // 杜門 - 提高 evade
            msg = HIG"$N在查克拉異常增值的情況下，連身影都變的有些糢糊...\n\n"NOR;
            add_temp("apply/evade", 300);
            break;
        default: // 判斷�婼炸堨�
            message_vision("\n$N使出"HIG"「影舞葉」"NOR"將$n打上空中，但右手隨即用手腕繃帶纏住$n將$n拉向左手使出"GRN+BLINK"『�堙E蓮華』"NOR"！\n", this_object(), enemy);
            if( !COMBAT_D->isHit(this_object(), enemy) ) {
                message_vision("但$n用蠻力硬是將繃帶扯碎，成功躲過了攻擊。\n"NOR, this_object(), enemy);
            } else {
                raiseDamage = 500*i;

                add_temp("apply/attack", raiseDamage); 
                damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                add_temp("apply/attack", -raiseDamage);

                if( damage < 200*i ) damage = (50 + random(150))*i;

                enemy->receive_damage(damage, this_object());
                message_vision( sprintf("$N將查克拉衝向$n的體內，令$n五臟六腑受到嚴重的衝擊，全身經脈也因此受到劇烈傷害！"NOR"(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
            }
            break;
    }
    if( query_temp("eight_pe") ) {
        delete_temp("eight_pe");
        message_vision(HIR"\n過度使用八門遁甲會產生負作用，$N關閉了八門遁甲。\n\n"NOR, this_object());
        if( i > 3 ) {
            add_temp("apply/evade", -300);
            delete_skill("sock power");
        }
        cnd["name"] = HIR+"(CD)八門"+NOR;
        cnd["duration"] = j*4;
        i = 0;
        j = 0;

        set_condition("soft_cd", cnd);
        if( query_condition("da") ) delete_condition("da");
        start_busy(3);
    } else if( !query_condition("soft_cd") ) {
        message_vision(msg, this_object());
        i++;
        start_busy(3);
    }
    return;
}

void to_do_say()
{
    if( i > 0 || query_condition("soft_cd") ) {
        message_vision(CYN"$N調適自己的身體，讓八門遁甲的負作用消到最低。\n"NOR, this_object());
        delete_condition("soft_cd");
        if( i > 3 ) {
            add_temp("apply/evade", -300);
            delete_skill("sock power");
        }
        if( this_object()->query_condition("da") ) this_object()->delete_condition("da");
        i = 0;
    }
    switch( random(100) ) {
        case 0..5:
            do_chat( ({ (: command, "say 青春！汗水！眼淚！喔∼∼阿剎∼∼" :) }) );
            break;
        case 20..25:
            do_chat( ({ (: command, "say 眼淚是青春的印記！" :) }) );
            break;
        case 40..45:
            do_chat( ({ CYN"小李突然趴在地上做起了伏地挺身！\n"NOR, }) );
            break;
        case 60..65:
            do_chat( ({ CYN"小李突然倒立了起來！\n"NOR, }) );
            break;
        case 80..85:
            do_chat( ({ CYN"小李眼睛突然發亮說道：請跟我交往，我這一輩子都會保護你的！\n"NOR, }) );
            break;
    }
    do_heal();
}

void create()
{
    set_name("李洛克", ({ "small lee", "lee" }));
    set_race("human");
    set_level(50);
    set_class("middle");            // 中忍
    set("classify", "strengthen");  // 強化
    set("camp", "muye");
    set("long", "小李是木葉村裡的忍者，是阿凱老師的學生，小李是個體術高手，但\n"
                "卻不會忍術和幻術，他的冬菇頭和濃眉讓人印像深刻，由於他最感激\n"
                "阿凱老師的熱誠，所以從髮型到服裝都受到阿凱老師的感染。\n");

    set("title", "熱血");
    set("age", 16);
    set("gender", "male");
    
    // 一般時動作
    set("chat_chance", 10);
    set("chat_msg", ({
        (: to_do_say :),
    }) );

    // 戰鬥時動作
    set("chat_chance_combat", 30);
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
    set_train_with_camp("combat", 1, 1, 160, "muye", -2);              // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 140, "muye", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 100, "muye", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 140, "muye", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 120, "muye", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 140, "muye", -2);       // 連擊之術
    set_train_with_camp("force", 1, 10, 180, "muye", -2);              // 體術
    set_train_with_camp("muye wind", 0, 15, 160, "muye", -1);          // 體術：木之葉烈風
    set_train_with_camp("muye cyclone", 1, 20, 140, "muye", 0);        // 體術：木之葉旋風
    set_train_with_camp("eight shell", 0, 21, 60, "muye", 0);          // 體術：八門遁甲
    setup();
    set_skill("combat", 200);
    set_skill("heavy hit", 200);
    set_skill("continual hit", 200);
    set_skill("dodge", 200);
    set_skill("force", 200);
    set_skill("muye wind", 200);
    set_skill("muye cyclone", 200);
    set_skill("eight shell", 120);

    // 附加能力，等高能力有點差
    add_temp("apply/intimidate", 150);  // 攻擊技巧
    add_temp("apply/wittiness", 50);    // 防禦技巧
    add_temp("apply/exact", 250);       // 命中能力
    add_temp("apply/str", 20);
    add_temp("apply/con", 10);
}

void relay_say(object ob, string arg)
{
    if( arg == "阿凱" || arg == "阿凱老師") {
        command("giggle");
        do_chat(({
            (: command, "say 阿凱老師是我最敬重的老師了。" :),
            (: command, "say 他時常鼓勵和熱心的教導我們，我最感激阿凱老師的真誠。" :),
            "說著說著，小李突然做起了伏地挺身，真是熱血！\n",
        }));
    }
}

void die()
{
    object enemy, killer;
    int i = 20 + random(11);
    string msg;

    enemy = this_object()->last_damage_giver();

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
    msg = HIW"\n還沒打敗寧次...還沒完成當初答應阿凱老師的心願！\n\n"HIG"怎麼能夠在這裡就被打敗！這樣曾經失敗再站起來又有什麼意義呢！\n\n"NOR;
    msg += HIG"【"HIR"木葉快訊"HIG"】"HIG"擁有木葉體術禁技「"HIY"八門遁甲"HIG"」傳承的忍者"+this_object()->query("name")+"，居然被"+enemy->query("name")+HIG"給擊敗了...\n\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
