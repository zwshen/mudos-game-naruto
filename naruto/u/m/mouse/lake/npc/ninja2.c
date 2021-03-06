#include <npc.h>
#include <ansi.h>

inherit F_BANDIT;

string *name1 = ({ "江津", "流雨", "秋水", "河合", "水波", "海", "暴雨", "河落", "江丘",
                   "海原", "湖氏", "天河", "春雨", "里海", "江", "天渦", "百湖", "冰銜",
                });
string *name2 = ({ "大次郎", "小次郎", "彌次郎", "水次郎", "靈波", "魚人", "凌秋","白",
                  "自在", "一郎", "二郎", "三郎", "四郎", "五郎", "汐潮", "洪河", "月",
                  "光海", "空", "蛹", "太久", "蹦太君", "瞬",
                });
void do_fight()
{
    int damage;
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
    if( this_object()->query_temp("quest/watershield") == 1) {
    return notify_fail("招式還沒退功，不能再使用。\n");
    } else {
    message_vision("$N結出『"CYN"水遁"NOR"』之印後雙手在身旁畫出一個巨大的圓形「"HIC"水障壁"NOR"」\n", this_object(), enemy);
    message_vision("        圓形漸漸發出光芒圍住$N，使$N的防禦增加了數倍！\n", this_object(), enemy);
    this_object()->start_busy(2);
    set_temp("apply/armor", 150);
    this_object()->add_temp("quest/watershield", 1);
    call_out("watershield_1",120,this_object(),enemy);
    }
}
void watershield_1()
{
    object enemy;
    message_vision("$N身旁的光芒漸漸退去，防禦也減弱了。\n", this_object(), enemy);
    set_temp("apply/armor", 0);
    this_object()->delete_temp("quest/watershield");
    return;
}
void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "ninja" }));
    set_race("human");
    set_level(25+random(3));
    set("age", 15+random(50));
    set("long", "雨隱村忍者，身上背了許多寶藏庫的寶藏準備烙跑。\n");
    set("attitude", "aggressive");         // 主動攻擊
    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    // 戰鬥動作
    set("chat_chance_combat", 15);
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
    // 技能
    set_skill("ninja", 90);
    set_skill("force", 90);
    set_skill("parry", 60);
    set_skill("combat", 80);
    set_skill("heavy hit", 60);
    set_skill("savage hit", 60);
    // 增強攻擊, 因有特功的關係降低防禦
    set_temp("apply/attack", 100);        // 攻擊力量
    set_temp("apply/exact", 20);          // 命中率
    set_temp("apply/intimidate", 20);     // 攻擊能力
}
