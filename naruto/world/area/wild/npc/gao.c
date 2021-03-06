#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void do_fight()
{
    mapping cnd = ([]);
    int damage, i, exact, evade;
    object enemy;
    object *inv;
    inv = all_inventory(environment(this_object()));

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( !inv ) return;
    if( !this_object() ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    exact = this_object()->query_level();

    this_object()->damage_stat("mp", 15, this_object());
    message_vision("$N收起武器施展"HIW"『發』"NOR"，只見$N的念力忽然轉換為"GRN"綠色氣體"NOR"擴散到四周...\n", this_object(), enemy);

    cnd["name"] = HIG"中毒"NOR;
    cnd["duration"] = 10;

    for(i=0;i<sizeof(inv);i++) {
        if( inv[i] == this_object() ) continue;
        if( !this_object()->visible(inv[i]) ) continue;
        if( environment()->is_area() && !area_environment(this_object(), inv[i])) continue;
        if( living(inv[i]) ) {
            if( inv[i]->is_corpse() ) continue;
            evade = inv[i]->query_level();

            if( COMBAT_D->SkillHit(this_object(), inv[i], exact, evade) ) {
                message_vision(HIG"$N不小心將綠氣吸入幾口，輕咳了幾聲...\n"NOR, inv[i]);
                inv[i]->add_busy(1);
                inv[i]->set_condition("vp", cnd);
            } else {
                message_vision("結果綠氣沒有對$N造成影響。\n", inv[i]);
            }
        }
    }
    return;
}
void create()
{
    set_name("盜高", ({ "dao gao", "gao" }));
    set_class("middle");
    set_level(35);
    set("title", "盜之首");
    set("long", "高約一尺的人，看他一副兇狠的模樣，就知道他是這裡兇惡盜賊的首\n"
                "領。不過現在的首領似乎已經不是他了，因為木葉村忍者伊乃森喜比\n"
                "不斷的尋找忍者攻擊此地，同時獵人公會也將這裡的盜賊列為重要攻\n"
                "擊對向，使得盜賊們一度差點被擊潰，結果來了一位自稱魔高的奇怪\n"
                "男子，居然使用特殊的技巧將忍者和獵人都擊退了，因此盜高便將首\n"
                "領之位讓給了魔高，還說服手下與自己一起和魔高學習技巧。\n");
    set("camp", "hole_bandit");
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":2000+random(1000), "p1":50, "p2":100 ]), // 銀子
        ([ "type":"obj", "id":22, "amount":1, "p1":20, "p2":100 ]),                 // 黃金牙
        ([ "type":"wp", "id":16, "amount":1, "p1":1, "p2":500 ]),                   // 高原劍
        ([ "type":"wp", "id":70, "amount":1, "p1":1, "p2":800 ]),                   // 山峰劍
        ([ "type":"eq", "id":66, "amount":1, "p1":5, "p2":100 ]),                   // 盜道鞋
        ([ "type":"eq", "id":67, "amount":1, "p1":10, "p2":100 ]),                  // 青銅護腕
    }) );
    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();

    // 增強
    add_temp("apply/attack", 100);
    add_temp("apply/armor", 60);
    add_temp("apply/exact", 20);
    add_temp("apply/evade", 20);
    add_temp("apply/intimidate", 10);
    add_temp("apply/wittiness", 10);
    add_temp("apply/int", 7);
    add_temp("apply/con", 7);
    add_temp("apply/str", 7);
    add_temp("apply/dex", 7);
}
