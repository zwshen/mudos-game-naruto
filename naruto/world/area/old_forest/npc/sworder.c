#include <npc.h>
#include <ansi.h>
#include "wp.h"

void do_fight()
{
    if( query_ability("attack") > query_ability("defend")) {
        message_vision(HIW"\n$N將武器高舉唸了幾句土語，左手換劍右手換盾，白光籠罩$N將攻防互調了。\n\n"NOR, this_object());
        add_temp("apply/attack", -300);
        add_temp("apply/armor", 300);
    } else {
        message_vision(HIW"\n$N將武器高舉唸了幾句土語，左手換盾右手換劍，白光籠罩$N將攻防互調了。\n\n"NOR, this_object());
        add_temp("apply/attack", 300);
        add_temp("apply/armor", -300);
    }
    return;
}
void create()
{
    set_name("土著女劍士", ({ "aborigines sworder", "sworder" }) );
    set_level(50);
    set_race("human");
    set("gender", "female");
    set("attitude", "aggressive");
    set("wp_number", 1);
    set("age", 15+random(41));
    set("nickname",HIY"威嚴"NOR);
    set("long", "身穿半罩式盔甲，頭上戴著土著部落中有一定身份地位才能配帶的白\n"
                "樹果面具，背上背著一柄幾乎連正常男性都無法輕鬆舉起的寬劍，散\n"
                "發著威風與超凡的氣勢，她就是土著女劍士。\n");
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
    add_temp("apply/hp", random(150));
    carry_object(_DIR_AREA_"thorn_pine/npc/wp/spiral_sword.c")->wield("righthand");
    call_out("die_1", 120+random(240), this_object());
    do_heal();
}

void die_1()
{
    message_vision(GRN"$N看了一看四周，又躲回叢林中了。\n"NOR, this_object());
    destruct(this_object());
    return;
}
