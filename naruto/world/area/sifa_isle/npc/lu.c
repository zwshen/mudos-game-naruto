#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // 訓練導師

void do_fight()
{
    object enemy, area;
    int damage, raiseDamage, exact, evade;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    // 貓貓果實-豹型態，已經用過才用技能
    if( !query("fruit_cat", 1) ) {
        message_vision(CYN"\n$N使用動物系『"HIY"貓貓果實"NOR"─"BLINK+HIR"豹型態"NOR+CYN"』的效果，慢慢變化成了獵豹！\n\n"NOR, this_object());

        set_skill("sock power", 50);              // 新技能，專門用來提高致命機率，mob專用
        set_skill("sock bom", 50);                // 新技能，專門用來提高致命傷害，mob專用
        set_skill("body iron", 200);              // 增加鐵塊發動率
        add_temp("apply/wittiness", 150);         // 防禦能力
        add_temp("apply/intimidate", 200);        // 攻擊能力
        add_temp("apply/exact", 100);             // 命中
        add_temp("apply/evade", 150);             // 迴避
        set("name", "羅布路奇"HIR"[豹型態]"NOR);  // 名字修正

        message_vision("$N說道﹕"HIG"只有動物系的果實，才能將我的實力完整呈現！\n"NOR, this_object(), enemy);
        set("fruit_cat", 1);
        return;
    }
    switch( random(2) ) {
        case 0: // 指槍•撥
            exact = COMBAT_D->intimidate(this_object(), 1);
            evade = COMBAT_D->wittiness(enemy, 1);

            message_vision("\n$N"HIY"伸出右手，食指與拇指輕輕一撥，彈出有如子彈般的"YEL"「指槍•"BLINK"撥"NOR+YEL"」\n"NOR, this_object(), enemy);
            if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
                message_vision(HIB"$N"HIB"馬上運用勁道將指槍角度打偏，在牆壁打出一個彈孔。\n\n"NOR, enemy);
                start_busy(2);
            } else {
                raiseDamage = 1100;
                add_temp("apply/attack", raiseDamage); 
                damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                add_temp("apply/attack", -raiseDamage);
                enemy->receive_damage(damage, this_object());
                message_vision( sprintf(RED"$n"NOR+RED"被指槍擊中，身上貫穿了一個像彈孔般的傷害！流血不止(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
            }
            break;
        case 1: // 豹尾
            if( query("fruit_cat", 1) && !enemy->is_busy() ) {
                exact = COMBAT_D->exact(this_object(), enemy, 1)/2;

                add_temp("apply/exact", exact);
                message_vision("\n$N"HIY"使出"HIW"「剃刀」"HIY"用著超越剃的速度直接衝到$n"HIY"眼前，企圖用豹尾卷住$n"HIY"！\n"NOR, this_object(), enemy);
                if( !COMBAT_D->isHit(this_object(), enemy) ) {
                    message_vision(HIK"$n"HIK"立刻無差別攻擊四周，令"NOR"$N"HIK"無法靠近。\n\n"NOR, this_object(), enemy);
                    enemy->start_busy(1);
                } else {
                    message_vision(YEL"$N"NOR+YEL"來不及逃走，被豹尾卷起，無法行動了！\n\n"NOR, enemy);
                    enemy->start_busy(5);
                }
                add_temp("apply/exact", -exact);
                break;
            }
        default: // 六王槍
            if( query("fruit_cat", 1) && enemy->is_busy() ) {
                message_vision("\n\n$N說道﹕"HIG"只有將六式全都練到極致的人，才能使用的最強招式...\n\n"NOR, this_object());
                message_vision("$N"HIK"趁著$n"HIK"無法行動之即，以最快的速度使出"HIC"[月步]"HIW"[剃]"HIK"快速接近$n\n"HIK"就在兩人距離一臂之隔時，"NOR"$N"HIK"伸出雙手抵住$n"HIK"胸口，發動奧義\n\n\t\t"HIM"『 "NOR+RED+BLINK"六　"HIR"王　"NOR+WHT+BLINK"槍 "NOR+HIM"』\n\n"NOR, this_object(), enemy);
                raiseDamage = 5000;
                add_temp("apply/attack", raiseDamage); 
                damage = COMBAT_D->isDamage(this_object(), enemy, 0);
                add_temp("apply/attack", -raiseDamage);
                enemy->receive_damage(damage, this_object());
                message_vision( sprintf(HIR"簡單的雙拳發出比"HIY"[指槍]"HIR"還要強勁的穿透力、比"HIB"[嵐腳]"HIR"還強的破壞力、氣勁鋼如"HIW"[鐵塊]"HIR"、\n卻又像"NOR+CYN"[紙繪]"HIR"般在體內四處流竄，給予了$n無可抵禦的嚴重傷害！(%d) %s\n\n"NOR, damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                start_busy(1);
                enemy->start_busy(2);
            }
            break;
    }
    return;
}
void check_fruit()
{
    // 沒在戰鬥要回復成人型
    if( query("fruit_cat", 1) ) {
        set("name", "羅布路奇");              // 名字修正
        message_vision(CYN"$N一言不語的變回了人型。\n"NOR, this_object());
        delete("fruit_cat");
        delete_skill("sock power");
        delete_skill("sock bom");
        set_skill("body iron", 180);          // 減少鐵塊發動率
        add_temp("apply/wittiness", -150);    // 防禦能力
        add_temp("apply/intimidate", -200);   // 攻擊能力
        add_temp("apply/exact", -100);        // 命中
        add_temp("apply/evade", -150);        // 迴避
    }
    delete_condition("fb_busy");              // 清除紙繪武身冷卻
    do_heal();
    return;
}
void create()
{
    set_name("羅布路奇", ({ "lu ji", "lu", "ji" }) );
    set_race("human");
    set_level(80);
    set_class("general_sea");       // 海軍准將
    set("classify", "strengthen");  // 強化
    set("age", 28);
    set("title", HIR"ＣＰ９"NOR);
    set("long", "臉上面無表情，被稱為冷酷的殺人機器，海軍諜報機構ＣＰ９的最強\n"
                "成員「羅布•路奇」。根據海兵間的謠傳，有次政府遇到一件五百名\n"
                "海軍士兵被大海賊團俘虜的事件，當時政府幾乎考慮要向海賊團投降\n"
                "時，派出了年僅十三歲的路奇潛入海賊基地，殺光了海軍五百名的俘\n"
                "虜，並在海賊團嚴密炮擊中砍下了海賊團長的頭，結束了這個事件。\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向路奇學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    set("chat_chance", 20);
    set("chat_msg", ({
        (: check_fruit :),
    }) );
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    // 選則海軍還是海賊並沒有影響
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 200, "police", -2);              // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 180, "police", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 180, "police", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 200, "police", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 180, "police", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 180, "police", -2);       // 連擊之術
    set_train_with_camp("martial", 1, 10, 200, "police", -2);            // 武術基礎
    set_train_with_camp("gun finger", 1, 15, 180, "police", 1);          // 武術：指槍
    set_train_with_camp("gun ban", 0, 20, 140, "police", 0);             // 武術：指槍•斑
    set_train_with_camp("gun gentian", 0, 40, 80, "police", 2);         // 武術：指槍•黃蓮
    set_train_with_camp("fight body", 1, 15, 160, "police", 0);          // 武術：紙繪武身

    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":10+random(11), "p1":100, "p2":100 ]),   // 黃金
        ([ "type":"eq", "id":10, "amount":1, "p1":90, "p2":100 ]),                 // 汗衫
    }) );
    setup();
    set_skill("combat", 200);
    set_skill("dodge", 200);
    set_skill("parry", 200);
    set_skill("heavy hit", 200);
    set_skill("savage hit", 200);
    set_skill("continual hit", 200);
    set_skill("martial", 200);
    set_skill("gun finger", 200);
    set_skill("gun ban", 200);
    set_skill("gun gentian", 200);
    set_skill("fight body",200);
    set_skill("body iron", 180);
    set_skill("paper step", 160);

    add_temp("apply/exact", 100);       // 命中
    add_temp("apply/evade", 100);       // 迴避
    add_temp("apply/intimidate", 200);  // 攻擊技巧
    add_temp("apply/wittiness", 100);   // 防禦技巧
    add_temp("apply/str", 40);
    add_temp("apply/dex", 10);

    carry_object(__DIR__"eq/pants.c")->wear();
    carry_object(__DIR__"eq/suit.c")->wear();
}
int accept_kill(object me, string arg)
{
    if( this_object()->query_condition("fb_busy", 1) == 0) {
        message_vision("$N說道﹕"HIG"居然敢動手，找死。\n"NOR, this_object());
        command("perform fight body.check");
    } else {
        message_vision("$N說道﹕"HIG"想死就成全你。\n"NOR, this_object());
    }
}
int accept_fight(object me, string arg)
{
    do_chat( ({
        (: command, "say ...." :),
        (: command, "say 有任務在身別來搗亂。" :),
    }) );
    return 0;
}
void die()
{
    object enemy, killer;
    int i;
    string msg;

    enemy = this_object()->last_damage_giver();
    i = 135 + random(16);

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
    msg = "\n\n"HIR"世界政府的警報響起！各方官員士兵四處奔走，似乎在傳遞什麼訊息！\n忽然四方傳來了一陣驚人的怒吼聲！居然是"NOR+YEL"戰國元帥"HIR"在動怒了！\n\n"NOR+YEL"戰國元帥"NOR"："HIG"那個"+enemy->query("name")+"是什麼來頭！？什麼？"HIY+enemy->rank()+HIG"！？\n"NOR+YEL"戰國元帥"NOR"："HIG"居然能擊敗ＣＰ９六式頂尖高手的羅布路奇！？"NOR"\n\n"HIR"只見"NOR+YEL"戰國元帥"HIR"立刻頒布新的命令，讓各地的海軍必須注意"+enemy->query("name")+"這號人物...\n但是海軍們都懼怕於"+enemy->query("name")+"的能力，根本不敢正視這項新法令...\n\n"NOR;
    msg += HIB"【世界政府】"+enemy->query("name")+"("+enemy->query("id")+")擊敗了擁有"HIK"「黑暗的正義」"HIB"稱號的"+this_object()->query("name")+HIB"("+this_object()->query("id")+")已經傳遍世界各地了。\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死羅布路奇獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
