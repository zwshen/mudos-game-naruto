#include <npc.h>

inherit F_BANDIT;

string *name1 = ({ "東", "疤", "陳", "拓", "亞摩", "葛蕾", "蝙", "喳", "磊", "靡",
                   "喬", "史", "西西", "龍", "索", "鮑", "伊目", "烏", "阿", "吉塔", 
                   "尖", "勾", "疾" , "皆", "細", "卡娜", "華石", "智", "殺", "狸狽" });

string *name2 = ({ "巴", "彭", "立", "鬥", "理", "塔", "都特", "唬", "露特", "稽",
                   "尼", "跋", "圖耳", "酉", "彌", "得羅", "禮", "穆", "更", "喇苦",
                   "美", "四", "鬥", "卜戎", "寬", "莉亞", "鬥郎", "喜", "大索", "多" });

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
    switch( this_object()->query("sktree") ) {
        case 1: // 肉體強化
            if( !mapp(this_object()->query_condition("body_strength_cond")) )
            command("perform strength.powerup");
            break;

        case 2: // 火念力變化
            break;

        case 3: // 冰念力變化
            break;

        case 4: // 念彈
            command("perform emit.shoot on " + enemy->query_id());
            break;

        case 5: // 血球再生
            if( !mapp(this_object()->query_condition("blood_cell_revive_cond")) )
            command("perform operation.revive on " + this_object()->query_id());
            break;

        case 6: // 聖療之手
            if( this_object()->query_stat("hp") < 301 ) {
            command("perform special.healing on " + this_object()->query_id());
            }
            break;
    }
}
void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "hunter", "__HUNTER__" }));
    set_race("human");
    set_level(20);
    set("age", 12+random(40));
    set("long", "無照獵人考生，正迫不及待的想盜取你的號碼牌。\n");
    set_class("hxh_initial");
    set("attitude", "aggressive");         // 主動攻擊
    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));

    // 戰鬥動作
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":50+random(50), "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"obj", "id":69, "amount":1, "p1":25, "p2":100 ]),  // 號碼牌
    }) );

    set("sktree", random(6)+1);

    setup();

    // 狀態
    set_stat_current("hp", 800);
    set_stat_current("ap", 800);
    set_stat_current("mp", 800);
    set_stat_maximum("hp", 800);
    set_stat_maximum("ap", 800);
    set_stat_maximum("mp", 800);

    // 技能, 簡化平時擁有的sk, 將特殊sk放入sktree中才習得

    delete_skill("ninja");  // 刪除獵人不該有的
    delete_skill("magic");
    delete_skill("force");

    set_skill("parry", 90);
    set_skill("dodge", 90);
    set_skill("combat", 90);
    set_skill("heavy hit", 90);
    set_skill("savage hit", 90);
    set_skill("continual hit", 90);
    set_skill("solid", 90);                         // 堅
    switch( query("sktree") ) {
        case 1: // 肉體強化
            set_skill("strength", 90);              // 強化系
            set_skill("body strength", 90);
            map_skill("strength", "body strength");
            break;
        case 2: // 火念力變化
            set_skill("variation", 90);             // 變化系
            set_skill("fire variation", 90);
            map_skill("combat", "fire variation");
            break;
        case 3: // 冰念力變化
            set_skill("variation", 90);             // 變化系
            set_skill("ice variation", 90);
            map_skill("combat", "ice variation");
            break;
        case 4: // 念彈
            set_skill("emit", 90);                  // 放出系
            set_skill("psychical bullet", 90);
            map_skill("emit", "psychical bullet");
            break;
        case 5: // 血球再生
            set_skill("operation", 90);             // 操作系
            set_skill("blood-cell revive", 90);
            map_skill("operation", "blood-cell revive");
            break;
        case 6: // 聖療之手
            set_skill("special", 90);               // 特質系
            set_skill("holy hand", 90);
            map_skill("special", "holy hand");
            break;
    }
    // 增強
    set_temp("apply/attack", 150);        // 攻擊力量
    set_temp("apply/armor", 50);          // 防禦力量
    set_temp("apply/exact", 37);          // 命中率
    set_temp("apply/evade", 50);          // 迴避率
    set_temp("apply/intimidate", 10);     // 攻擊能力
    set_temp("apply/wittiness", 10);      // 防禦能力
    set_temp("apply/int", 5);
    set_temp("apply/con", 5);
    set_temp("apply/str", 5);
    set_temp("apply/dex", 5);
}
