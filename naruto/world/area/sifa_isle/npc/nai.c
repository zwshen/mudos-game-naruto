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
    // 嵐腳
    command("perform kick haze.kick on " + enemy->query_id() );
}
void to_do_say()
{
    do_chat( ({ 
        (: command, "say 搞什麼！政府特殊機構就是在這裡收新進人員的嗎！" :),
        (: command, "say 想「加入」海軍的話就問吧，沒事別煩我。" :),
        (: command, "say 真搞不懂長官在想什麼..." :),
    }) );
}

void create()
{
    set_name("奈洛", ({ "nai luo", "nai", "luo" }) );
    set_race("human");
    set_level(40);
    set_class("officer_sea");  // 海軍士官
    set("age", 20);
    set("title", HIR"ＣＰ９新人"NOR);
    set("long", "剛加入海軍秘密組織的人，以前曾經是個殺手。只見他似乎不太滿意\n"
                "現在的工作，一直碎碎唸著：居然在新生召募處招收新進人員，我可\n"
                "是政府特殊機構的成員！好歹也該來點像樣的工作！\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向奈洛學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    // 海賊王部份，海軍海賊可互相學習技能
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 120, "police", -2);           // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 120, "police", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 120, "police", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 100, "police", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 100, "police", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 100, "police", -2);    // 連擊之術
    set_train_with_camp("martial", 1, 10, 120, "police", -2);         // 武術基礎
    set_train_with_camp("spurn", 1, 10, 120, "police", -2);           // 踢技基礎
    set_train_with_camp("activity", 1, 10, 120, "police", -2);        // 特殊基礎
    set_train_with_camp("body iron", 1, 10, 100, "police", 0);        // 鐵塊
    set_train_with_camp("paper step", 1, 10, 100, "police", 0);       // 紙繪
    set_train_with_camp("gun finger", 1, 15, 100, "police", -1);      // 武術：指槍
    set_train_with_camp("kick haze", 1, 15, 120, "police", -1);       // 踢技：嵐腳

    setup();
    set_skill("martial", 150);
    set_skill("spurn", 150);
    set_skill("body iron", 100);
    set_skill("paper step", 100);
    set_skill("gun finger", 120);
    set_skill("kick haze", 120);
}

// 當char用say指令時，此mob的回應
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "加入" || arg == "加入海軍" ) {
        if( me->query("guild") ) {
            if( me->query("guild") == "piece") {
                do_chat( ({ 
                    (: command, "say "+this_player()->query("name")+"已經聽過我說了吧！" :),
                    (: command, "say 要加入海軍去找斯潘達姆長官！" :),
                    (: command, "say 長官人應該在艾尼艾斯大廳二樓吧！" :),
                }) );
                return 1;
            }
            do_chat( ({ 
                (: command, "say "+this_player()->query("name")+"已經加入別的組織啦！" :),
                (: command, "say 別來浪費我的時間！" :),
            }) );
            return 1;
        }
        me->set("guild", "piece");
        me->set("title", "海軍入門者");
        do_chat( ({
            (: command, "say 海賊跟海軍的技能可以互相學習。" :),
            (: command, "say 不過因為陣營對立一見面會立刻開打。" :),
            (: command, "say 所以加入前再好好考慮一次吧！" :),
            (: command, "say 如果要加入海軍，就到艾尼艾斯二樓找斯潘達姆長官！" :),
        }) );
        return 1;
    }
    return 1;
}
