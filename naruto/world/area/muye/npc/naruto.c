#include <npc.h>

inherit F_FIGHTER;
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
    command("perform thousand year kill.attack on " + enemy->query_id() );
    return;
}
void create()
{
    set_name("漩渦鳴人", ({ "naruto" }));
    set_race("human");
    set_level(50);
    set_class("inferior");   // 下忍
    set("camp", "muye");
    set("long", "喜歡惡作劇的鳴人，是木葉村的問題兒童，在忍者學校也是個「吊車\n"
                "尾」的學生。因為身上被尾獸「九尾狐」所附身，所以小時候村人都\n"
                "不願意靠近他，直到伊魯卡老師對他打開心房加上後來加入卡卡西小\n"
                "隊發生大蛇丸襲擊事件等，之後便跟著三忍之一的自來也學習忍術。\n");

    set("age", 16);
    set("gender", "male");
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
    set_train_with_camp("dodge", 1, 1, 100, "muye", -2);               // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 120, "muye", -2);               // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 120, "muye", -2);           // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 140, "muye", -2);          // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 120, "muye", -2);       // 連擊之術
    set_train_with_camp("ninja", 1, 10, 120, "muye", -2);              // 忍術
    set_train_with_camp("force", 1, 10, 140, "muye", -2);              // 體術
    set_train_with_camp("alter ego", 0, 15, 140, "muye", -1);          // 忍術：分身術
    set_train_with_camp("shadow", 0, 20, 120, "muye", -1);             // 忍術：影分身術
    set_train_with_camp("thousand year kill", 0, 21, 100, "muye", 0); // 體術：千年殺

    setup();
    set_skill("ninja", 160);
    set_skill("force", 180);
    set_skill("thousand year kill", 200);
    set_skill("substitute", 200);
    map_skill("dodge", "substitute");
}
