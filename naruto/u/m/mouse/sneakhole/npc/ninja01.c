#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

string *name1 = ({ "音舞", "聲宿", "律子", "絢華", "樂", "妙", "曲譜",
                   "奏鳴", "響", "漫音", "空悲" });

string *name2 = ({ "歌", "迷", "爍", "彩", "繞", "旋", "夢", "惑", "靡",
                   "飄搖", "獨享", "悠然", "平靜", "共鳴", "無畏",
                   "和合子", "好自在", "空無窮" });

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_fight()
{
    int damage;
    object enemy;
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( this_object()->query_temp("quest/throw_dart") == 2) {
        message_vision("$N"HIR"順著剛才射程"NOR"$n"HIR"的鈴聲，順手又擲出兩根刺針！\n"NOR, this_object(), enemy);
        damage = 100+random(71);
        if( random(enemy->query_ability("evade")) > 150) {
            message_vision("        $n快速的從旁邊滾了開來。(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->delete_temp("quest/throw_dart");
            this_object()->start_busy(1);
            return;
        }
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n「噗」的一聲被刺針射中，痛的哇哇大叫。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        return;
    } else
    if( this_object()->query_temp("quest/throw_dart") == 1) {
        message_vision("$N"HIG"聽著刺中"NOR"$n"HIG"風笛的聲音，快速擲出鈴噹飛刀！\n"NOR, this_object(), enemy);
        damage = 30+random(61);
        if( random(enemy->query_ability("evade")) > 170) {
            message_vision("        $n快速的從旁邊滾了開來。(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->delete_temp("quest/throw_dart");
            this_object()->start_busy(1);
            return;
        }
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n「噗」的一聲被飛刀射中，行動鈍了一下。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        this_object()->add_temp("quest/throw_dart", 1);
        return;
    }
    message_vision("$N"HIY"朝著"NOR"$n"HIY"射出一把飛針，針順著風傳出鳴笛聲！\n"NOR, this_object(), enemy);
    damage = 10+random(51);
    if( random(enemy->query_ability("evade")) > 230) {
        message_vision("        $n快速的從旁邊滾了開來。(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->delete_temp("quest/throw_dart");
        this_object()->start_busy(1);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        $n「噗」的一聲被飛針射中，腳部受了一點傷害。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    this_object()->add_temp("quest/throw_dart", 1);
    return;
}
void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "ninja" }));
    set_race("human");
    set_level(28+random(3));
    set("gender", "female");
    set("nickname",HIM"音之忍者"NOR);
    set("age", 10+random(51));
    set("attitude", "aggressive");
    set("long", "音隱村的忍者，似乎正在這裡進行什麼工程。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: command, "say 小看我會讓你後悔的！" :),
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"wp", "id":5, "amount":1, "p1":15, "p2":100 ]),               // 苦無
        ([ "type":"obj", "id":29, "amount":50+random(100), "p1":80, "p2":100 ]),// 銀子
        ([ "type":"food", "id":51, "amount":1, "p1":7, "p2":100 ]),             // 燒賣
        ([ "type":"food", "id":10, "amount":1, "p1":6, "p2":100 ]),             // 豚骨
        ([ "type":"food", "id":11, "amount":1, "p1":2, "p2":100 ]),             // 正油
        ([ "type":"eq", "id":89, "amount":1, "p1":1, "p2":400 ]),               // 護腰
        ([ "type":"eq", "id":90, "amount":1, "p1":1, "p2":300 ]),               // 護額
    }) );
    setup();
}
