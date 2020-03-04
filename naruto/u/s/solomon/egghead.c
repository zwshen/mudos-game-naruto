#include <ansi.h>
inherit NPC;
void create()
{
    set_name(HIC"小蛋頭"NOR, ({ "Little egghead" , "egghead" }) );
    set_race("human");
    set_level(80);
    set("long", "他是一位蛋佬的僕人，忠心耿耿，年輕力壯，是蛋佬不可多得的好幫手。\n");
    set("age",18);
    set("title", HIM"蛋佬的僕人"NOR);
    set("chat_chance",10);
    set("chat_msg", ({ 
HIY"小蛋頭低聲說道：要快點打掃這邊，不然就倒大楣囉。\n"NOR,
HIG"小蛋頭大聲自豪地說道：蛋佬交代下來的工作，我從來沒有搞砸過！！\n"NOR,
HIC"小蛋頭喘息道：總算把最後一個工作給做完囉，好累好累。\n"NOR,
YEL"小蛋頭一邊吹著口哨，一邊輕鬆地唱歌∼∼∼\n"NOR,
                   (:command("tsk"):),
                   (:command("walileh"):),
                   (:command("sing"):),
                   (:command("laugh"):),
 }));
    setup();
}

void init()
{     
   object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}


void greeting(object ob)
{
 object me = this_player();
 if ( !me || environment(me) != environment() ) return; 
 
 command("hi "+ me->query("id"));
}
