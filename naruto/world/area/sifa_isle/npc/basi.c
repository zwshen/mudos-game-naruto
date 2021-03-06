#include <npc.h>
#include <ansi.h>

inherit F_SEASOLDIER;

void to_do_say()
{
    do_chat( ({ 
        NOR"左邊的頭說道﹕"HIG"左邊的我叫做「左巴斯卡比魯！」\n"NOR,
        NOR"右邊的頭說道﹕"HIG"右邊的我叫做「右巴斯卡比魯！」\n"NOR,
        CYN"中間的頭「嗯」的一聲﹐一副欲言又止的樣子。\n"NOR,
        NOR"中間的頭大喊﹕"HIG"中央的我就叫做「中央橫貫公路！」\n"NOR,
        (: command, "hit kabilu" :),
        NOR"左右巴斯卡比魯同聲說道﹕"HIG"你是誰阿！\n"NOR,
    }) );
}
void create()
{
    set_name("巴斯卡比魯", ({ "basi kabilu", "basi", "kabilu" }) );
    set_race("human");
    set_level(45);
    set("age", 75);
    set("camp", "police");
    set("title", HIR"宙判長"NOR);
    set("long", "司法島的大法官，奇怪的是他居然有三個頭，簡直就像地獄的守門犬\n"
                "一樣。三個頭之間還有互相的交談，意見似乎也不太一樣，不過他們\n"
                "對於臺下的被審者都是給予同樣的答覆。「死刑！」\n");

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":100+random(300), "p1":50, "p2":100 ]),  // 銀子
        ([ "type":"obj", "id":28, "amount":1, "p1":50, "p2":100 ]),                // 黃金
        ([ "type":"wp", "id":53, "amount":1, "p1":1, "p2":500 ]),                  // 雙翼刃
        ([ "type":"eq", "id":104, "amount":1, "p1":5, "p2":100 ]),                 // 司法裁判戒
        
    }) );
    setup();
    carry_object(_DIR_WP_"longsword.c")->wield();
    add_temp("apply/armor", 200);
}
void die()
{
    object enemy, killer;
    string msg;

    enemy = this_object()->last_damage_giver();

    if( !enemy ) {
        ::die();
        return;
    }
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) {
            ::die();
            return;
        } else
        if( environment(enemy) != environment(this_object()) ) {
            ::die();
            return;
        }
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = "\n\n"HIY+this_object()->query("name")+"痛苦的大喊：要是讓我抓到你，我一定會判你死刑的！\n"NOR;
    msg += HIR"\n"HIR"【社會新聞】"+this_object()->query("name")+"("+this_object()->query("id")+")死於"+enemy->rank()+enemy->query("name")+"("+enemy->query("id")+")之手了！\n\n"NOR;

    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    if( random(100) < 30 ) {
        killer->add("exchange", 1);
        tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 1 點兌換點數。)\n"NOR);
    }
    ::die();
    return;
}
