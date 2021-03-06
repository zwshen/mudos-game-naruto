// write by -Acme-

#include <npc.h>

inherit F_VILLAGER;
inherit F_TRAINER;    // 訓練忍者

/* guild: muye   木葉忍者村
          yinyin 音隱忍者村
          wuyin  霧隱忍者村
          shayin 砂隱忍者村
          yuyin  雨隱忍者村
          yunyin 雲隱忍者村
          caoyin 草隱忍者村
          puyin  瀑隱忍者村
*/

void create()
{
    set_name("辛心長", ({ "sin sin zhang master", "master" }) );
    set_race("human");
    set_level(40);
    set_class("superior");    //上忍
    set("age", 35);
    set("title", "新手導師");
    set("long", "他是一位新手學院裡專聘的教師，教導新手一些基本技能，你可以利\n"
                "用 train 指令來學習一些基本的技能。\n"
                "用 list 指令查詢可以學習的技能列表。\n");

    // 設定忍者村，相同的忍者村才會教, 設定 all 不分忍者村
    set("guild", "all");

    // 設定能訓練的技能
    //
    // set_train(技能名, 是否可直接習得, 學習該技能所需要的角色等級, 此技能可學習到的上限等級)
    //
    // 當玩家沒有該技能時，若"是否可直接習得"這個設定值為非零值時，玩家向訓練者學習時則可記住
    // 這個技能到lv1，而有lv的技能才可以投點繼續鍛練。故可用於特殊技，要解謎得到lv後方可訓練。
    //
    set_train("combat", 1, 1, 100);               // 格鬥技巧             F級
    set_train("dodge", 1, 1, 100);                // 閃躲技巧             F級
    set_train("parry", 1, 1, 100);                // 擋格技巧             F級
    set_train("heavy hit", 1, 5, 100);            // 重擊之術             F級
    set_train("savage hit", 1, 5, 100);           // 暴擊之術             F級
    set_train("continual hit", 1, 5, 100);        // 連擊之術             F級
/*
    set_train("force", 1, 10, 100);               // 體術                 F級
    set_train("ninja", 1, 10, 100);               // 忍術                 F級
    set_train("magic", 1, 10, 100);               // 幻術                 F級
*/
/*
    set_train("alter ego", 0, 20, 100);           // 忍術：分身術         
    set_train("substitute", 0, 15, 100);          // 忍術：替身術         
    set_train("shadow", 0, 50, 100);              // 忍術：影分身術       
    set_train("thunder cut", 0, 60, 100);         // 忍術：雷切           S級
    set_train("reincarnation", 0, 80, 100);       // 忍術：穢土轉生       S級
    set_train("moon dance", 0, 55, 100);          // 忍術：彎月舞         A級
    set_train("wind blade", 0, 60, 100);          // 忍術：風刃           A級
    set_train("snake kill", 0, 65, 100);          // 忍術：雙蛇相殺術     A級
    set_train("water-water fall", 0, 50, 100);    // 忍術：水遁•大瀑布術 A級
    set_train("water-water dragon", 0, 40, 100);  // 忍術：水遁•水龍彈術 B級
    set_train("plover", 0, 55, 100);              // 忍術：千鳥           A級
    set_train("soul dies", 0, 45, 100);           // 忍術：死魂術         B級
    set_train("puppet", 0, 35, 100);              // 忍術：傀儡術         C級
    set_train("whirlwind", 0, 30, 100);           // 忍術：旋風術         C級
    set_train("fire-dragon fire", 0, 30, 100);    // 忍術：火遁•龍火術   C級
    set_train("fire-bold fireball", 0, 25, 100);  // 忍術：火遁•豪火球術 C級
    set_train("fire-phoenix fire", 0, 20, 100);   // 忍術：火遁•鳳仙火術 C級
    set_train("animal taming", 0, 10, 100);       // 忍術：馴獸術         E級
    set_train("bad worm", 0, 40, 100);            // 忍術：寄壞蟲術       -級
    set_train("sand burial", 0, 40, 100);         // 忍術：砂瀑送葬       -級
    set_train("sand tie", 0, 30, 100);            // 忍術：砂縛柩         -級
    set_train("sand armor", 0, 50, 100);          // 忍術：砂盔甲         -級
    set_train("sand shield", 0, 60, 100);         // 忍術：砂盾           -級

    set_train("inside lotus", 0, 60, 100);        // 體術：�婼炸�         A級
    set_train("outside lotus", 0, 50, 100);       // 體術：表蓮華         B級
    set_train("shadow leaf", 0, 30, 100);         // 體術：影舞葉         C級
    set_train("lion attack", 0, 30, 100);         // 體術：獅子連彈       C級
    set_train("muscle tank", 0, 25, 100);         // 體術：肉彈戰車       C級
    set_train("thousand year kill", 0, 20, 100);  // 體術：千年殺         E級
    set_train("double physique", 0, 30, 100);     // 體術：倍化術         -
    set_train("sixty palms", 0, 50, 100);         // 體術：八卦六十四掌   -
    set_train("sky palm", 0, 40, 100);            // 體術：八卦掌回天     -

    set_train("five elements seal", 0, 70, 100);  // 封印：五行封印術     A級
    set_train("five elements unseal", 0, 70, 100);// 封印：五行解印術     A級
*/
    setup();

    // 人物本身的技能設定
    set_skill("dodge", 200);               // 基本： 迴避技巧
    set_skill("parry", 200);               // 基本： 防禦技巧
    set_skill("combat", 200);              // 基本： 格鬥技巧
    set_skill("savage hit", 200);          // 基本： 暴擊
    set_skill("heavy hit", 200);           // 基本： 重擊
    set_skill("continual hit", 200);       // 基本： 連擊
    set_skill("force", 180);               // 基本： 體術
    set_skill("ninja", 200);               // 基本： 忍術
    set_skill("substitute", 180);          // 忍術： 替身術

    map_skill("dodge", "substitute");      // 使用技能「替身術」於迴避技巧上
}
