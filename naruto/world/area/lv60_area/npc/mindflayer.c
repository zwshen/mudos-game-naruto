#include <npc.h>
#include <ansi.h>

string *name = ({ HIW"", HIK"", HIC"", HIY"", HIM"",
                  HIB"", HIG"", HIR"", REV"" });
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
        case 1: // 嵐腳 & 嵐腳•孤狼
            if( random(3) == 0 ) {
                command("perform kick haze.kick on " + enemy->query_id());
            } else {
                command("perform kick wolf.kick on " + enemy->query_id());
            }
            break;
        case 2: // 風速計 & 幻想妖精
            if( this_object()->query_condition("elf") == 0 ) command("perform chimera fay.assoil");
            break;
        case 3: // 念彈 & 雙手機關槍
            command("perform psychical bullet.shoot on " + enemy->query_id());
            break;
        case 4: // 火念力變化 & 火牆
            if( this_object()->query_condition("firewall") == 0 ) command("perform fire wall.fire");
            break;
        case 5: // 白眼 & 八卦六十四掌
            if( this_object()->query_condition("white_eyes") != 0 ) command("perform soft fist.attack on " + enemy->query_id());
            else command("perform white eyes.open");
            break;
        case 6: // 倍化術 & 肉彈戰車
            if( this_object()->query_condition("dp") != 0 ) command("perform muscle tank.attack on " + enemy->query_id());
            else command("perform double physique.dp");
            break;
    }
}

void do_move()
{
    object ob = this_object();
    if( ob->query("sktree") ==6 && ob->query_condition("white_eyes") != 0 ) delete_condition("white_eyes");
    else do_chat((: random_move :));
}

void create()
{
    set_name( name[random(sizeof(name))]+"奪心魔"NOR, ({ "mindflayer" }));
    set_race("human");
    set_level(40);
    set("age", 300 + random(5000));
    set("long", "圓形的身軀上長著一顆巨大的眼睛，眼睛中閃爍五顏六色的光芒，讓\n"
                "人容易陷於迷惑之中。身軀的四角長著四隻觸手，用來接觸其他生物\n"
                "以奪取其心智。奪心魔擅長使用魔法技巧，連平常的移動都是以漂浮\n"
                "的狀態行進，可知其魔法能力的強大。\n");

    set("attitude", "aggressive");         // 主動攻擊
    set("sktree", random(6)+1);            // 技能判斷

    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: do_move :),
    }));

    // 戰鬥動作
    set("chat_chance_combat", 35);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // 隨機道具
    switch( random(1000) ) {
        case 0..350:
            set("set_drop", ({
                ([ "type":"obj", "id":130, "amount":1, "p1":15, "p2":100 ]),  // 妖魂
                ([ "type":"obj", "id":28, "amount":1, "p1":30, "p2":100 ]),   // 黃金
            }) );
            break;
        case 650..1000:
            set("set_drop", ({
                 ([ "type":"obj", "id":131, "amount":1, "p1":15, "p2":100 ]),  // 龍魂
                ([ "type":"obj", "id":28, "amount":1, "p1":30, "p2":100 ]),   // 黃金
            }) );
            break;
        case 351..649:
             set("set_drop", ({
                 ([ "type":"obj", "id":132, "amount":1, "p1":10, "p2":100 ]),  // 心魂
                 ([ "type":"obj", "id":28, "amount":1, "p1":30, "p2":100 ]),   // 黃金
             }) );
             break;
    }
    setup();

    // 狀態
    set_stat_current("hp", 3500);
    set_stat_current("ap", 2500);
    set_stat_current("mp", 5000);
    set_stat_maximum("hp", 3500);
    set_stat_maximum("ap", 2500);
    set_stat_maximum("mp", 5000);

    // 基本技能
    set_skill("parry", 160);
    set_skill("dodge", 160);
    set_skill("combat", 160);
    set_skill("heavy hit", 160);
    set_skill("savage hit", 160);
    set_skill("continual hit", 160);

    // 隨機補助防技
    switch( random(4) ) {
        case 0: set_skill("substitute", 160);
                map_skill("dodge", "substitute");
                break;
        case 1: set_skill("solid", 160);
                map_skill("parry", "solid");
                break;
        case 2: set_skill("body iron", 160);
                break;
        case 3: set_skill("paper step", 160);
                break;
    }
    switch( query("sktree") ) {
        case 1: // 嵐腳 & 嵐腳•孤狼
            set_skill("spurn", 160);
            set_skill("kick haze", 160);
            set_skill("kick wolf", 160);
            set_skill("sock power", 50);
            break;
        case 2: // 風速計 & 幻想妖精
            carry_object("/world/area/ship/npc/wp/sky_stick.c");
            set_skill("activity", 160);
            set_skill("anemometer", 160);
            set_skill("chimera fay", 160);
            break;
        case 3: // 念彈 & 雙手機關槍
            set_skill("emit", 160);
            set_skill("psychical bullet", 160);
            set_skill("machine gun", 160);
            break;
        case 4: // 火念力變化 & 火牆
            set_skill("variation", 160);
            set_skill("fire variation", 160);
            set_skill("fire wall", 160);
            break;
        case 5: // 白眼 & 八卦六十四掌
            set_skill("force", 160);
            set_skill("white eyes", 160);
            set_skill("soft fist", 160);
            break;
        case 6: // 倍化術 & 肉彈戰車
            set_skill("force", 160);
            set_skill("double physique", 160);
            set_skill("muscle tank", 160);
            break;
    }
    // 增強
    add_temp("apply/exact", 100);       // 命中率
    add_temp("apply/evade", 100);       // 迴避率
    add_temp("apply/intimidate", 150);  // 攻擊能力
    add_temp("apply/wittiness", 150);   // 防禦能力
    add_temp("apply/int", 5);
    add_temp("apply/con", 5);
    add_temp("apply/str", 5);
    add_temp("apply/dex", 5);
    call_out("die_1", 240+random(240), this_object());
}

void die_1()
{
    message_vision("$N"HIK"又潛回了黑暗之中。\n"NOR, this_object());
    destruct(this_object());
    return;
}
