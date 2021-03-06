#include <npc.h>
#include <ansi.h>

inherit F_SEABANDIT;

string *name = ({ "槍", "鞭", "圖章", "火箭炮", "網",
                  "槍亂打", "螺旋彈", "戰斧", "攻城炮" });

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$N" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$N" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$N" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_fight()
{
    object enemy;
    int damage, i;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( query("two_down", 1) ) {
        message_vision("\n$N"HIR"臉上露出一絲霸氣，右腳連續輕踏地面"HIW"「剃」"HIR"突然消失在$n的眼前！！\n"NOR, this_object(), enemy);
        for(i=0;i<=3;i++) {
            damage = random(query_ability("attack")) + query_ability("attack");
            message_vision(CYN"\n$N一個瞬間出現在$n的身旁！\n"NOR, this_object(), enemy);
            if( random(query_ability("exact")) + query_ability("exact")/5 < random(enemy->query_ability("evade")) ) {
                message_vision("$n一招"HIY"橡膠 JET "+name[random(sizeof(name))]+NOR"像風一般掃過$N的臉頰，在地上轟出個大洞。"+report_status(enemy)+"", enemy, this_object());
                this_object()->start_busy(1);
            } else {
                enemy->receive_damage(damage, this_object());
                message_vision("$n使出"HIY"橡膠 JET "+name[random(sizeof(name))]+NOR"！強勁的力道立刻把$N擊飛了出去！("+damage+")"+report_status(enemy)+"", enemy, this_object());
                enemy->start_busy(3);
            }
        }
        message_vision(HIR"\n\n$N收回了連續攻擊！\n\n"NOR, this_object(), enemy);
    } else {
        message_vision("$N怒吼著："HIG"想拿我的草帽！不可原諒！看我的"HIY"橡膠"+name[random(sizeof(name))]+NOR+HIG"！！！\n"NOR, this_object(), enemy);
        damage = random(query_ability("attack")) + query_ability("attack")/2;
        if( random(query_ability("exact")) + 50 > random(enemy->query_ability("evade")) ) {
            message_vision("\t$N好不容易驚險萬分的閃了開來！(0)"+report_status(enemy)+"", enemy, this_object());
            this_object()->start_busy(3);
        } else {
            enemy->receive_damage(damage, this_object());
            message_vision("\t$N不知道被打中了幾拳，全身沒一處是完整的。("+damage+")"+report_status(enemy)+"", enemy, this_object());
            this_object()->start_busy(1);
        }
     }
     return;
}

void to_do_say()
{
    if( query("two_down", 1) ) {
        message_vision(CYN"$N喘了口氣，身上二檔的效果漸漸消失了。\n"NOR, this_object());
        delete("nickname");
        add_temp("apply/exact", -600);
        add_temp("apply/evade", -600);
        add_temp("apply/intimidate", -300);
        add_temp("apply/wittiness", -300);
        delete("two_down");
        do_heal();
    }
    if( random(200) == 100 ) {
        do_chat( ({
            CYN"魯夫無聊的唸著：怎麼還不能吃飯∼\n"NOR,
            CYN"魯夫大叫著：我要吃肉！吃肉！\n"NOR,
            CYN"魯夫大叫著：香吉！開飯拉∼∼∼∼∼！\n"NOR,
        }) );
    }
}

void create()
{
    set_name("魯夫", ({ "luffy" }) );
    set_race("human");
    set_level(60);
    set_class("money_sea");  // 通緝海賊
    set("age", 15);
    set("title", HIY"帶草帽的"NOR);
    set("long", "被世界政府重金懸賞的可怕海賊，但是看他滿臉笑容的樣子一點也不\n"
                "像是十惡不赦的大海賊。只見他悠閒的躺在黃金梅莉號的羊頭上休息\n"
                "臉上蓋著他的標準配備，也是與某人重要約定的無價之寶─"HIY"草帽"NOR"。\n");

    // 一般時動作
    set("chat_chance", 1);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    set("chat_chance_combat", 80);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"eq", "id":103, "amount":1, "p1":1, "p2":100 ]),       // 草帽
        ([ "type":"food", "id":47, "amount":1, "p1":80, "p2":100 ]),     // 蟹肉
        ([ "type":"food", "id":68, "amount":1, "p1":80, "p2":100 ]),     // 魚肉
        ([ "type":"food", "id":75, "amount":1, "p1":80, "p2":100 ]),     // 鯊魚肉
        ([ "type":"food", "id":76, "amount":1, "p1":30, "p2":100 ]),     // 海賊便當
    }) );

    setup();
    set_skill("combat", 200);
    set_skill("parry", 200);
    set_skill("dodge", 200);
    set_skill("heavy hit", 200);
    set_skill("savage hit", 200);
    set_skill("continual hit", 200);
    add_temp("apply/exact", 100);       // 命中
    add_temp("apply/evade", 100);       // 迴避
    add_temp("apply/intimidate", 150);  // 攻擊能力
    add_temp("apply/wittiness", 150);   // 防禦能力
    add_temp("apply/con", 20);
    add_temp("apply/str", 10);
}

void die()
{
    object luffy, enemy;

    if( query("two_down", 1) ) {
        ::die();
        return;
    }
    luffy = new(__DIR__"luffy.c");
    enemy = this_object()->query_opponent();

    if( !enemy ) enemy = this_object()->last_damage_giver();

    if( environment(this_object())->is_area() ) move_side(luffy, this_object());
    else luffy->move(environment(this_object()));

    luffy->set("nickname", HIW+BLINK"二檔"NOR);
    luffy->add_temp("apply/exact", 500);
    luffy->add_temp("apply/evade", 500);
    luffy->add_temp("apply/intimidate", 150);
    luffy->add_temp("apply/wittiness", 150);
    luffy->set("two_down", 1);

    message_vision("\n$N說道﹕"HIG"好痛阿！可惡！我生氣了！\n"NOR, luffy);
    message_vision(CYN"$N雙手壓住自己的膝蓋，像個蒸氣機般不停打氣。\n"NOR, luffy);
    message_vision(CYN"$N全身噴出白色蒸氣，發出沙沙聲響！\n"NOR, luffy);
    message_vision("\n$N說道﹕"HIG"進入•二檔。\n\n"NOR, luffy);

    luffy->kill_ob(enemy);
    if( function_exists("accept_kill", enemy) && !enemy->is_killing(luffy) && enemy->accept_kill(luffy) ) return;
    enemy->kill_ob(luffy);
    return;
}

int accept_fight(object me, string arg)
{
    do_chat( ({
        (: command, "shake" :),
        (: command, "say 我餓了不想打架" :),
    }) );
    return 0;
}
