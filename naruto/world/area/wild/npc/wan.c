#include <npc.h>

inherit F_VILLAGER;

void to_do_say()
{
    do_chat( ({ 
        (: command, "say 唉呀呀∼ 全身乏力，真難受啊！" :),
        (: command, "say 什麼時候才能進補啊∼" :),
    }) );
}

void create()
{
    set_name("捕蛇丸" , ({ "bu she wan", "wan" }) );
    set("long", "一位看起來有了一點年紀，且滿臉歷經滄桑的感覺。\n");

    set_level(45);

    set("gender", "male");
    set("title", "「來就捕」" );
    set("age", 62);

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: to_do_say :),
    }) );

    setup();

}

void relay_say(object ob, string arg)
{
    if( arg == "進補" || arg == "藥" || arg == "湯藥" || arg == "燉藥" || arg == "藥材")  {
        do_chat( ({ 
            (: command, "say 秦琴這丫頭說要幫我補補身子，怎麼都沒有動靜。" :),
        }) );
        return;
    }
}
