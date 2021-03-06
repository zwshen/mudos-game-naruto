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
    // 阿凱目前能開六門
    if( (i == 1 || i == 3) && random(5) < 2 ) {
        set_temp("eight_pe", 1);
    } else {
        if( i < 6 ) message_vision(HIR"\n$N雙手握拳，將全身的查克拉集中在周身大穴..."NOR"\n$N說道﹕"HIG"八門遁甲 第"HIY+chinese_number(i+1)+HIG"門•"+door[i]+HIG"，開！！\n\n"NOR, this_object());
    }
    switch( i ) {
        case 0:  // 開門 - 表蓮華
            msg = HIG"只見$N額頭上冒出青筋，身體似乎充滿了力量。\n\n"NOR;
            break;
        case 1:  // 休門 - 查克拉補滿
            if( !query_temp("eight_pe") ) {
                msg = HIG"$N身上查克拉含量正以異常快的速度回復中！\n\n"NOR;
                this_object()->set_stat_current("mp", query_stat_maximum("mp"));
            } else {
                message_vision("\n$N忽然間加快速度一記「"YEL"掃堂腿"NOR"」將$n踢至空中，接著雙腳蹬地躍向$n！\n"NOR, this_object(), enemy);
                if( !COMBAT_D->isHit(this_object(), enemy) ) {
                    message_vision("但是$n在空中一個轉身，就這樣順利避開了$N的突襲。\n"NOR, this_object(), enemy);
                } else {
                    raiseDamage = 1200;

                    add_temp("apply/attack", raiseDamage); 
                    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                    add_temp("apply/attack", -raiseDamage);

                    if( damage < 600 ) damage = random(200) + 400;

                    enemy->receive_damage(damage, this_object());
                    message_vision( sprintf("$n被$N牢牢抓住"HIR"『表•蓮華』"NOR"快速從空中撞向地面，將$n撞的血肉糢糊！(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                }
            }
            break;
        case 2:  // 生門 - �婼炸�
            msg = HIG"$N身上所含的查克拉量已經超出身體存量，開始溢出體外造成天搖地動！\n\n"NOR;
            break;
        case 3:  // 傷門 - 加速體力回復 (使用海賊的消化吸收buff)
            if( !query_temp("eight_pe") ) {
                msg = HIG"溢出體外的查克拉快速包圍$N的傷口，居然使$N體力異常快速回復！\n\n"NOR;

                cnd["name"] = HIR+"八門-傷"+NOR;
                cnd["duration"] = query_skill("eight shell", 1);
                cnd["hp"] = query_stat_maximum("hp")/50;

                set_condition("da", cnd);
            } else {
                message_vision(HIG"\n$N用極快的速度對$n"HIG"腰間踢出數腳，右掌一擊將$n"HIG"打向空中！"NOR"\n正當$n尚未飛到頂點之際，$N左手已經凝聚了八門遁甲所釋放的過多查克拉"GRN+BLINK"『�堙E蓮華』"NOR"！\n\n", this_object(), enemy);
                if( !COMBAT_D->isHit(this_object(), enemy) ) {
                    message_vision("但$n巧妙地擊向左手手腕，成功將這招的攻擊傷害轉移在空氣中。\n"NOR, this_object(), enemy);
                } else {
                    raiseDamage = 2000;

                    add_temp("apply/attack", raiseDamage); 
                    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                    add_temp("apply/attack", -raiseDamage);

                    if( damage < 800 ) damage = random(300) + 500;

                    enemy->receive_damage(damage, this_object());
                    message_vision( sprintf(HIY"四周傳出強烈的衝擊波，連石頭樹木都被擊毀，被此招擊中的$n"HIY"更是身受重傷！"NOR"(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                }
            }
            break;
        case 4:  // 杜門 - 提高 evade
            msg = HIG"$N在查克拉異常增值的情況下，連身影都變的有些糢糊...\n\n"NOR;
            add_temp("apply/evade", 300);
            break;
        case 5:  // 景門 - 提高致命一擊機率
            msg = HIG"$N爆吼一聲，已經壓制不住體內不斷括散的查克拉，終於忍不住出手了！\n\n"NOR;
            set_skill("sock power", 100);
            break;
        case 6:  // 朝孔雀
            set_temp("eight_pe", 1);

            raiseDamage = 400;

            add_temp("apply/attack", raiseDamage);
            set_skill("sock power", 200);
            message_vision(HIR"\n$N雙拳噴出火紅的查克拉使出必殺"RED"『"NOR+BRED+BLINK"朝孔雀"NOR+HIR"』雙拳不停地往$n的身上招呼！！\n\n"NOR, this_object(), enemy);

            for(j=0;j<7;j++) {
                COMBAT_D->fight(this_object(), enemy, this_object());
                if( enemy->query_stat_current("hp") <= 100 ) {
                    j = 9;
                    message_vision(HIR"\n$n"HIR"已經撐不住了，", this_object(), enemy);
                }
            }
            if( j != 10 ) message_vision("\n", this_object());
            set_skill("sock power", 100);
            add_temp("apply/attack", -raiseDamage);
            message_vision(HIR"$N將攻勢停了下來！\n", this_object());
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
        cnd["duration"] = i*4;
        i = 0;

        set_condition("soft_cd", cnd);
        if( query_condition("da") ) delete_condition("da");
    } else {
        message_vision(msg, this_object());
        i++;
    }
    start_busy(3);
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
        case 0..10:
            do_chat( ({ 
                (: command, "say 身為男子漢就是要熱血！" :),
            }) );
            break;
        case 20..30:
            do_chat( ({ 
                (: command, "say 來吧！跟著我一起舞動！" :),
            }) );
            break;
        case 40..50:
            do_chat( ({ 
                CYN"阿凱比出右手大姆指，潔白的牙齒亮光一閃，讓人無法直視.\n"NOR,
            }) );
            break;
        case 60..70:
            do_chat( ({ 
                (: command, "say 這就是青春阿！" :),
            }) );
            break;
    }
    do_heal();
}

void create()
{
    set_name("阿凱", ({ "kai" }));
    set_race("human");
    set_level(70);
    set_class("superior");          // 上忍
    set("classify", "strengthen");  // 強化
    set("title", "熱情＆活力");
    set("camp", "muye");
    set("long", "阿凱是木葉村的熱血漢子，也是視卡卡西為敵的體術高手！他的冬菇\n"
                "頭和濃眉令人印像深刻！\n");

    set("age", 26);
    set("gender", "male");

    set("chat_chance", 10);
    set("chat_msg", ({
        (: to_do_say :),
    }) );

    set("chat_chance_combat", 25);
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
    set_train_with_camp("combat", 1, 1, 200, "muye", -2);              // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 200, "muye", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 180, "muye", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 200, "muye", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 200, "muye", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 180, "muye", -2);       // 連擊之術
    set_train_with_camp("ninja", 1, 10, 160, "muye", -2);              // 忍術
    set_train_with_camp("force", 1, 10, 200, "muye", -2);              // 體術
    set_train_with_camp("muye wind", 0, 15, 160, "muye", -1);          // 體術：木之葉烈風
    set_train_with_camp("muye cyclone", 0, 20, 140, "muye", 0);        // 體術：木之葉旋風
    set_train_with_camp("eight shell", 1, 21, 200, "muye", 0);         // 體術：八門遁甲

    setup();
    set_skill("ninja", 170);
    set_skill("force", 200);
    set_skill("muye wind", 200);
    set_skill("muye cyclone", 200);
    set_skill("eight shell", 200);
    set_skill("substitute", 200);
    map_skill("dodge", "substitute");

    // 附加能力，等高能力有點差
    add_temp("apply/intimidate", 200);  // 攻擊技巧
    add_temp("apply/exact", 250);       // 命中能力
    add_temp("apply/evade", 200);       // 迴避能力
    add_temp("apply/str", 15);
    add_temp("apply/con", 15);
}

void die()
{
    object enemy, killer;
    int i = 60 + random(16);
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
    msg = HIR"\n"+this_object()->query("name")+"嘴角流血地半跪在地上伸起大姆指比向"+enemy->query("name")+"說道：\n"HIG"『沒想到"+enemy->rank()+"也有這麼熱血的傢伙！果然活在這個世界上就是要熱血阿！！』\n\n"HIY"小李！老師先走一步了！等來到我這再教你更帥氣的新招式吧！\n\n"NOR;
    msg += HIG"【"HIR"木葉快訊"HIG"】"HIG"木葉一流體術高手"NOR+RED"「熱血ＭＡＸ！」"HIG"教師"+this_object()->query("name")+"被冷酷的"+enemy->query("name")+HIG"擊敗了。\n\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
