#include <npc.h>
#include <ansi.h>

inherit F_BANDIT;

string *name1 = ({ "江津", "流雨", "秋水", "河合", "水波", "海", "暴雨", "河落",
                   "江丘","海原", "湖氏", "天河", "春雨", "里海", "江", "天渦",
                   "百湖", "冰銜" });

string *name2 = ({ "大次郎", "小次郎", "彌次郎", "水次郎", "靈波", "魚人", "凌秋",
                   "白", "自在", "一郎", "二郎", "三郎", "四郎", "五郎", "汐潮",
                   "洪河", "月", "光海", "空", "蛹", "太久", "蹦太君", "瞬" });

void do_fight()
{
    mapping cnd = ([]);
    int damage;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( this_object()->query_condition("waterwall") != 0 ) {
        write("招式還沒退功，不能再使用。\n");
        return;
    }
    message_vision("\n$N結出『"CYN"水遁"NOR"』之印後雙手在身旁畫出一個巨大的圓形「"HIC"水障壁"NOR"」\n", this_object(), enemy);
    message_vision(HIC"圓形漸漸發出光芒圍住$N，使$N的防禦增加了數倍！\n\n"NOR, this_object(), enemy);

    cnd["name"] = HIC+"水障壁"+NOR;
    cnd["duration"] = 120;
    cnd["from"] = this_object();
    cnd["add"] = 200;
    cnd["ability"] = "armor";

    this_object()->damage_stat("mp", 50, this_object());
    this_object()->set_condition("waterwall", cnd);
    this_object()->start_busy(1);
    return;
}

void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "ninja" }));
    set_race("human");
    set_level(25+random(3));
    set("age", 15+random(50));
    set("nickname",HIC"雨之忍者"NOR);
    set("long", "雨隱村忍者，身上背了許多寶藏庫的寶藏準備烙跑。\n");
    set("camp", "rain");

    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    // 戰鬥動作
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
        (: command, "say 想跟我們雨隱搶寶藏？殺！" :),
    }) );

    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":50+random(50), "p1":60, "p2":100 ]),  // 銀子
        ([ "type":"wp", "id":5, "amount":1, "p1":10, "p2":100 ]),                // 苦無
        ([ "type":"obj", "id":49, "amount":1, "p1":40, "p2":100 ]),              // 古董花瓶
        ([ "type":"obj", "id":41, "amount":1, "p1":30, "p2":100 ]),              // 精緻娃娃
        ([ "type":"obj", "id":45, "amount":1, "p1":20, "p2":100 ]),              // 未知陶壺
        ([ "type":"obj", "id":48, "amount":1, "p1":10, "p2":100 ]),              // 木造藏
        ([ "type":"obj", "id":40, "amount":1, "p1":5, "p2":100 ]),               // 傳家之寶
    }) );
    setup();
    // 增強
    add_temp("apply/attack", 50);
    add_temp("apply/exact", 20);
    add_temp("apply/intimidate", 20);
}
