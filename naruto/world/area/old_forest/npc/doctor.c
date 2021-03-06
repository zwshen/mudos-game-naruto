#include <npc.h>
#include <ansi.h>
#include "wp.h"

void do_fight()
{
    mapping cnd = ([]);
    object enemy, bad;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( file_size(__DIR__"item/bad_pill.c") < 0 ) return;
    if( catch(bad = new(__DIR__"item/bad_pill.c")) ) return;

    message_vision(HIB"\n$N古怪的露出一抹怪笑，從懷裡摸出一顆"HIG"綠色豆子"HIB"丟向$n。\n"NOR, this_object(), enemy);

    if( !bad->move(enemy) ) {
        message_vision("但是$n的身上太重了，綠色豆子撞到$n後滾落到了一旁角落。\n"NOR, this_object(), enemy);
        destruct(bad);
        return;
    } else {
        bad->set_owner(enemy);
        bad->set("changed", 1);
    }
    return;
}
void create()
{
    set_name("土著老巫醫", ({ "aborigines doctor", "doctor" }) );
    set_level(50);
    set_race("human");
    set("gender", "male");
    set("attitude", "aggressive");
    set("wp_number", 2);
    set("age", 70+random(261));
    set("nickname",HIM"詭異"NOR);
    set("long", "滿臉皺紋的老土人，兩手卻有如嬰兒般的細嫩，據說是因為土著的巫\n"
                "醫們時常會到處尋找各種不同的藥材，有時緊急便會空手取藥，長久\n"
                "下來連皮膚也跟著變好了，由其老巫醫更是如此。\n");
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
    carry_object(__DIR__"wp/tree_staff.c")->wield("lefthand");
    call_out("die_1", 120+random(240), this_object());
    do_heal();
}

void die_1()
{
    message_vision(GRN"$N看了一看四周，又躲回叢林中了。\n"NOR, this_object());
    destruct(this_object());
    return;
}
