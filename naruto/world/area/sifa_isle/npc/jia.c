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
    // 犬犬果實-狼型態，已經用過才用孤狼
    if( !query("fruit_wolf", 1) ) {
        message_vision(CYN"\n$N使用動物系『"HIK"犬犬果實"NOR"─"BLINK+HIK"狼型態"NOR+CYN"』的效果，強化成狼型了！\n\n"NOR, this_object());

        set_skill("sock power", 100);           // 新技能，專門用來提高致命機率，mob專用
        set_skill("body iron", 200);            // 增加鐵塊發動率
        add_temp("apply/intimidate", 200);      // 攻擊能力
        add_temp("apply/wittiness", 150);       // 防禦能力
        add_temp("apply/evade", 100);           // 迴避
        add_temp("apply/exact", 150);           // 命中
        set("name", "賈布拉"HIK"[狼型態]"NOR);  // 名字修正

        message_vision("$N狼嚎般道："HIG"哈哈哈！讓$n"HIG"知道我鐵塊拳法的真正威力！ㄠ嗚嗚∼∼！\n"NOR, this_object(), enemy);
        set("fruit_wolf", 1);
        set("chat_chance_combat", 50);          // 增加使用技能機率
        return;
    }
    // 嵐腳•孤狼
    command("perform kick wolf.kick on " + enemy->query_id() );
    return;
}
void check_fruit()
{
    // 沒在戰鬥要回復成人型
    if( query("fruit_wolf", 1) ) {
        set("name", "賈布拉");                   // 名字修正
        message_vision(CYN"$N眼看沒人打擾，又恢復成人型倒頭就睡了。\n"NOR, this_object());
        delete("fruit_wolf");
        delete_skill("sock power");              // 新技能，專門用來提高致命機率，mob專用
        set_skill("body iron", 160);             // 減少鐵塊發動率
        add_temp("apply/intimidate", -200);      // 攻擊能力
        add_temp("apply/wittiness", -150);       // 防禦能力
        add_temp("apply/evade", -100);           // 迴避
        add_temp("apply/exact", -150);           // 命中
    }
    do_heal();
    return;
}
void create()
{
    set_name("賈布拉", ({ "jia bu la", "jia", "bu", "la", "_JIA_" }) );
    set_race("human");
    set_level(70);
    set_class("guard_sea");         // 海軍校衛
    set("classify", "strengthen");  // 強化
    set("age", 25);
    set("title", HIR"ＣＰ９"NOR);
    set("long", "穿著有點類似中國武術家，只見他無聊的躺在地上睡覺，一點都不\n"
                "擔心擺在旁邊的錢袋會被人拿走。居然還睡到鼻子上吹出了一個大\n"
                "泡泡，應該是完全睡著了吧，想偷拿錢袋嗎？\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向賈布拉學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    set("chat_chance", 20);
    set("chat_msg", ({
        (: check_fruit :),
    }) );
    // 自動技居多，降低手動技使用
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // 接受過奈洛的教學便加入海賊王部份
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
    set_train_with_camp("dodge", 1, 1, 160, "police", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 160, "police", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 160, "police", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 200, "police", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 140, "police", -2);    // 連擊之術
    set_train_with_camp("martial", 1, 10, 180, "police", -2);         // 武術基礎
    set_train_with_camp("spurn", 1, 10, 180, "police", -2);           // 踢技基礎
    set_train_with_camp("body iron", 1, 15, 140, "police", 0);        // 鐵塊
    set_train_with_camp("gun finger", 1, 15, 160, "police", -1);      // 武術：指槍
    set_train_with_camp("gun ten", 0, 35, 100, "police", 2);          // 武術：十指槍
    set_train_with_camp("kick wolf", 0, 20, 140, "police", 0);        // 踢技：嵐腳•孤狼
    set_train_with_camp("body skill", 0, 40, 80, "police", 2);       // 特殊：鐵塊拳法

    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":10+random(11), "p1":100, "p2":100 ]),   // 黃金
        ([ "type":"eq", "id":57, "amount":1, "p1":80, "p2":100 ]),                 // 狼腳
        ([ "type":"eq", "id":59, "amount":1, "p1":80, "p2":100 ]),                 // 狼腳
        ([ "type":"eq", "id":61, "amount":1, "p1":90, "p2":100 ]),                 // 狼尾
    }) );
    setup();
    set_skill("combat", 180);
    set_skill("dodge", 160);
    set_skill("parry", 160);
    set_skill("heavy hit", 160);
    set_skill("savage hit", 200);
    set_skill("continual hit", 140);
    set_skill("martial", 200);
    set_skill("spurn", 200);
    set_skill("kick wolf", 200);
    set_skill("gun finger", 200);
    set_skill("kick haze", 200);
    set_skill("gun ten", 200);
    set_skill("body skill", 200);
    set_skill("body iron", 160);
    set_skill("paper step", 150);

    add_temp("apply/evade", 50);        // 迴避
    add_temp("apply/intimidate", 150);  // 攻擊能力
    add_temp("apply/wittiness", 150);   // 防禦能力
    add_temp("apply/str", 25);
    add_temp("apply/con", 15);

    carry_object(__DIR__"eq/pants.c")->wear();
    carry_object(__DIR__"eq/suit.c")->wear();
}
void die()
{
    object enemy, killer;
    int i;
    string msg;

    enemy = this_object()->last_damage_giver();
    i = 60 + random(11);

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
    msg = "\n\n"HIK+this_object()->query("name")+HIK"口吐白沫倒在地上暈死了過去...\n\n"+enemy->query("name")+"抽著煙喃喃自語：大野狼還是去騙小紅帽吧...我可是"HIR+enemy->rank()+HIK"！\n\n"NOR;
    msg += HIB"【世界政府】ＣＰ９「六式」高手"+this_object()->query("name")+HIB"("+this_object()->query("id")+")居然被"+enemy->query("name")+"("+enemy->query("id")+")殺死了！\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死賈布拉獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}
