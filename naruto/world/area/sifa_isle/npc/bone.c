#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // 訓練導師

void create()
{
    set_name("Ｔ•彭恩", ({ "T bone", "bone" }) );
    set_race("human");
    set_level(40);
    set_class("officer_sea");  // 海軍士官
    set("age", 20);
    set("title", HIB"海軍總部上校"NOR);
    set("long", "海軍有名的將領，人稱「斬船俠」一刀可以將一隻海王類劈成兩半，\n"
                "因為討厭彎曲的刀法，所以使用的招式全都是直來直往的直角刀法。\n"
                "目前的工作是指導海軍新進人員學習技能。\n"
                "海賊和海軍技能可互相學習，利用 train 指令來向彭恩學習技能。\n"
                "使用 list 指令查詢可學習的技能列表。\n" );

    // 海賊王部份，海軍海賊可互相學習技能
    set("guild", "piece");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train_with_camp("combat", 1, 1, 100, "police", -2);           // 格鬥技巧
    set_train_with_camp("dodge", 1, 1, 100, "police", -2);            // 閃躲技巧
    set_train_with_camp("parry", 1, 1, 140, "police", -2);            // 擋格技巧
    set_train_with_camp("heavy hit", 1, 5, 120, "police", -2);        // 重擊之術
    set_train_with_camp("savage hit", 1, 5, 120, "police", -2);       // 暴擊之術
    set_train_with_camp("continual hit", 1, 5, 120, "police", -2);    // 連擊之術
    set_train_with_camp("blade", 1, 10, 140, "police", -2);           // 刀術基礎
    set_train_with_camp("blink normal", 1, 15, 160, "police", -1);    // 刀術：直角閃光
    set_train_with_camp("flybird normal", 1, 20, 140, "police", -1);  // 刀術：直角飛鳥

    setup();
    set_skill("blade", 180);
    set_skill("blink normal", 200);
    set_skill("flybird normal", 200);
    carry_object(_DIR_WP_"longsword.c")->wield();
}
